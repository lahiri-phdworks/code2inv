
#include <torch/torch.h>
#include <torch/script.h>

#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <math.h>
#include <libhfuzz/libhfuzz.h>
#include <inttypes.h>
// https://github.com/pytorch/examples/blob/master/cpp/mnist/mnist.cpp

#include <memory>
#include <cstddef>
#include <cstdio>
#include <iostream>
#include <string>
#include <vector>

// Where to find the MNIST dataset.
const char *kDataRoot = "./data/MNIST/raw";

// The batch size for training.
const int64_t kTrainBatchSize = 64;

// The batch size for testing.
const int64_t kTestBatchSize = 1;

template <typename DataLoader>
void test(
    torch::jit::Module &module,
    torch::Device device,
    DataLoader &data_loader,
    size_t dataset_size)
{
    torch::NoGradGuard no_grad;
    module.eval();

    double test_loss = 0;
    int32_t correct = 0, total = 0;

    for (const auto &batch : data_loader)
    {
        total += 1;
        auto data = batch.data.to(device);
        auto targets = batch.target.to(device);

        std::vector<torch::jit::IValue> mnist_input;
        std::vector<torch::jit::IValue> mnist_labelled_output;

        mnist_input.push_back(data);
        mnist_labelled_output.push_back(targets);

        auto output = module.forward(mnist_input).toTensor();

        test_loss += torch::nll_loss(
                         output,
                         targets,
                         /*weight=*/{},
                         torch::Reduction::Sum)
                         .template item<float>();

        auto pred = output.argmax(1);

        // To get the scalar out from a 1-D tensor at::Tensor Type.
        int target_number = targets.template item<int64_t>();
        int pred_number = pred.template item<int64_t>();

        std::printf(
            "\nPrediction : %d | Target : %d",
            pred_number, target_number);

        correct += pred.eq(targets).sum().template item<int64_t>();
    }

    std::printf(
        "\nStats : Correct : %d | Loss : %lf | DataSet Size : %ld | Total : %d",
        correct, test_loss, dataset_size, total);

    test_loss /= dataset_size;
    std::printf(
        "\nTest set: Average loss: %.4f | Accuracy: %.3f\n",
        test_loss,
        static_cast<double>(correct) / dataset_size);
}

template <typename DataLoader>
int32_t predict_single(FILE *fptr,
                       torch::jit::Module &module,
                       torch::Device device,
                       DataLoader &data_loader,
                       size_t dataset_size, int image_index)
{
    torch::NoGradGuard no_grad;
    module.eval();

    double test_loss = 0;
    int32_t correct = 0, total = 0, pred_number = 0;

    // auto dataset_iterator = data_loader.begin();

    for (const auto &batch : data_loader)
    {
        auto data = batch.data.to(device);
        auto targets = batch.target.to(device);

        int target_number = targets.template item<int64_t>();

        if (target_number == (image_index / 10))
        {

            std::vector<torch::jit::IValue> mnist_input;
            std::vector<torch::jit::IValue> mnist_labelled_output;

            mnist_input.push_back(data);
            mnist_labelled_output.push_back(targets);

            auto output = module.forward(mnist_input).toTensor();

            test_loss += torch::nll_loss(
                             output,
                             targets,
                             /*weight=*/{},
                             torch::Reduction::Sum)
                             .template item<float>();

            auto pred = output.argmax(1);
            pred_number = pred.template item<int64_t>();

            // std::fprintf(fptr,
            //              "Prediction : %d | Target : %d | Input Index : %d\n",
            //              pred_number, target_number, image_index);

            break;
        }
    }

    return pred_number;
}

int main(int argc, const char *argv[])
{

    char buff[2048];
    memset(buff, '\0', sizeof(buff));

    FILE *fptr = fopen("models.txt", "w");
    setvbuf(fptr, buff, _IOLBF, 2048);

    // Deserialize the ScriptModule from a file using torch::jit::load().
    // ./mnist_example ../<model.pt>
    torch::jit::Module module = torch::jit::load("./mnist_model_cpp.pt");

    torch::DeviceType device_type;
    device_type = torch::kCPU;
    torch::Device device(device_type);

    module.to(device);

    auto train_dataset = torch::data::datasets::MNIST(kDataRoot)
                             .map(torch::data::transforms::Normalize<>(0.1307, 0.3081))
                             .map(torch::data::transforms::Stack<>());
    const size_t train_dataset_size = train_dataset.size().value();
    auto train_loader =
        torch::data::make_data_loader<torch::data::samplers::SequentialSampler>(
            std::move(train_dataset), kTrainBatchSize);

    auto test_dataset = torch::data::datasets::MNIST(
                            kDataRoot, torch::data::datasets::MNIST::Mode::kTest)
                            .map(torch::data::transforms::Normalize<>(0.1307, 0.3081))
                            .map(torch::data::transforms::Stack<>());
    const size_t test_dataset_size = test_dataset.size().value();
    auto test_loader =
        torch::data::make_data_loader(std::move(test_dataset), kTestBatchSize);

    long long int sum = 0;

    for (;;)
    {
        size_t len;
        const uint8_t *buf;

        HF_ITER(&buf, &len);
        int input_index = buf[0];

        auto prediction = predict_single(fptr, module, device, *test_loader, test_dataset_size, input_index % 100);
        sum += prediction;
        std::fprintf(fptr,
                     "Prediction : %d | Sum : %d | Input Index : %d\n",
                     prediction, sum, input_index % 100);
    }
}

/**
 * sum = (((i/10)*((i/10)+1))/2), where i=0..9 are images of 0, i=10..19 are images of 1 and so on... 
*/