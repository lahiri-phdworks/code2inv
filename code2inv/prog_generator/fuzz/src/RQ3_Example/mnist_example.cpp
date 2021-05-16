
#include <torch/torch.h>
#include <torch/script.h> // One-stop header.
// https://github.com/pytorch/examples/blob/master/cpp/mnist/mnist.cpp

#include <memory>
#include <cstddef>
#include <cstdio>
#include <iostream>
#include <string>
#include <vector>

// Where to find the MNIST dataset.
const char *kDataRoot = "../data/MNIST/raw";

// The batch size for training.
const int64_t kTrainBatchSize = 64;

// The batch size for testing.
const int64_t kTestBatchSize = 1000;

// The number of epochs to train.
const int64_t kNumberOfEpochs = 10;

// After how many batches to log a new update with the loss value.
const int64_t kLogInterval = 10;

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
        std::cout << pred << std::endl;
        correct += pred.eq(targets).sum().template item<int64_t>();
    }

    std::printf(
        "\nStats : Correct : %d | Loss : %lf | DataSet Size : %ld | Total : %d\n",
        correct, test_loss, dataset_size, total);

    test_loss /= dataset_size;
    std::printf(
        "\nTest set: Average loss: %.4f | Accuracy: %.3f\n",
        test_loss,
        static_cast<double>(correct) / dataset_size);
}

int main(int argc, const char *argv[])
{

    // Deserialize the ScriptModule from a file using torch::jit::load().
    // ./mnist_example ../<model.pt>
    torch::jit::Module module = torch::jit::load(argv[1]);

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

    test(module, device, *test_loader, test_dataset_size);
}