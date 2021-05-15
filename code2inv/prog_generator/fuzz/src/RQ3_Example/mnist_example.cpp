
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
const int64_t kNumberOfEpochs = 1;

// After how many batches to log a new update with the loss value.
const int64_t kLogInterval = 10;

int main(int argc, const char *argv[])
{
    if (argc != 2)
    {
        std::cerr << "usage: example-app <path-to-exported-script-module>\n";
        return -1;
    }

    torch::jit::script::Module module;
    try
    {
        // Deserialize the ScriptModule from a file using torch::jit::load().
        module = torch::jit::load(argv[1]);
    }
    catch (const c10::Error &e)
    {
        std::cerr << "error loading the model\n";
        return -1;
    }

    torch::DeviceType device_type;
    if (torch::cuda::is_available())
    {
        std::cout << "CUDA available! Training on GPU." << std::endl;
        device_type = torch::kCUDA;
    }
    else
    {
        std::cout << "Training on CPU." << std::endl;
        device_type = torch::kCPU;
    }
    torch::Device device(device_type);

    auto test_dataset = torch::data::datasets::MNIST(
                            kDataRoot, torch::data::datasets::MNIST::Mode::kTest)
                            .map(torch::data::transforms::Normalize<>(0.1307, 0.3081))
                            .map(torch::data::transforms::Stack<>());

    const size_t test_dataset_size = test_dataset.size().value();

    auto test_loader =
        torch::data::make_data_loader(std::move(test_dataset), kTestBatchSize);

    auto train_dataset = torch::data::datasets::MNIST(kDataRoot)
                             .map(torch::data::transforms::Normalize<>(0.1307, 0.3081))
                             .map(torch::data::transforms::Stack<>());
    const size_t train_dataset_size = train_dataset.size().value();
    auto train_loader =
        torch::data::make_data_loader<torch::data::samplers::SequentialSampler>(
            std::move(train_dataset), kTrainBatchSize);

    torch::NoGradGuard no_grad;
    module.eval();

    double test_loss = 0;
    int32_t correct = 0;

    for (const auto &batch : *train_loader)
    {
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

    test_loss /= test_dataset_size;
    std::printf(
        "\nTest set: Average loss: %.4f | Accuracy: %.3f\n",
        test_loss,
        static_cast<double>(correct) / test_dataset_size);
}