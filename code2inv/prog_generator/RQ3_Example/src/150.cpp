
#include <torch/torch.h>
#include <torch/script.h>

#include <150.h>
#include <random>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
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

#define UNROLL_LIMIT 64

#define aflcrash(cond, flag) \
    if (!cond)               \
        flag = 1;

#define assume(cond) \
    if (!cond)       \
        continue;

#define INV(sum, n, i, index) PHI

long long unsigned int counter = 0;
int preflag = 0, loopflag = 0, postflag = 0;
long long unsigned int precount = 0, loopcount = 0, postcount = 0;

// COMMENT : Precheck template
void precheck(FILE *fptr, char *buff, long long int sum,
              long long int n, long long int i, long long int index)
{
    int f = preflag;
    aflcrash(INV(sum, n, i, index), preflag);
    if (f == 0 && preflag == 1)
    {
        fprintf(fptr, "Pre : %s : %lld, %s : %lld, %s : %lld, %s : %lld\n",
                "sum", sum, "n", n, "i", i, "index", index);
        assert(0);
    }
}

// COMMENT : Loopcheck template
void loopcheck(FILE *fptr, char *buff, long long int temp_sum, long long int temp_n, long long int temp_i,
               long long int temp_index, long long int sum, long long int n, long long int i, long long int index)
{
    int f = loopflag;
    aflcrash(INV(sum, n, i, index), loopflag);
    if (f == 0 && loopflag == 1)
    {
        fprintf(fptr, "LoopStart : %s : %lld, %s : %lld, %s : %lld, %s : %lld\n",
                "sum", temp_sum, "n", temp_n, "i", temp_i, "index", temp_index);
        fprintf(fptr, "LoopEnd : %s : %lld, %s : %lld, %s : %lld, %s : %lld\n",
                "sum", sum, "n", n, "i", i, "index", index);
        assert(0);
    }
}

// COMMENT : Postcheck template
#define postcheck(fptr, buff, cond, sum, n, i, index) \
    \ 
{                                                \
        \ 
    int f = postflag;                                 \
        \ 
   aflcrash(cond, postflag);                          \
        \ 
    if (f == 0 && postflag == 1)                      \
        {                                             \
            \ 
        fprintf(fptr, "Post : %s : %lld, %s : %lld, %s : %lld, %s : %lld\n", \ 
 "sum",                                               \
                sum, "n", n, "i", i, "index", index); \
            assert(0);                                \
        \ 
}                                            \
    }

FILE *fptr;

// Where to find the MNIST dataset.
const char *kDataRoot = "./data/MNIST/raw";

// The batch size for training.
const int64_t kTrainBatchSize = 64;

// The batch size for testing.
const int64_t kTestBatchSize = 1;

auto test_dataset = torch::data::datasets::MNIST(
                        kDataRoot, torch::data::datasets::MNIST::Mode::kTest)
                        .map(torch::data::transforms::Normalize<>(0.1307, 0.3081))
                        .map(torch::data::transforms::Stack<>());

const size_t dataset_size = test_dataset.size().value();

auto data_loader =
    torch::data::make_data_loader(std::move(test_dataset), kTestBatchSize);

int32_t predict(int image_index)
{
    // Deserialize the ScriptModule from a file using torch::jit::load().
    // ./mnist_example ../<model.pt>
    torch::jit::Module module = torch::jit::load("./mnist_model_cpp.pt");

    torch::NoGradGuard no_grad;
    module.eval();

    double test_loss = 0;
    int32_t correct = 0, total = 0, pred_number = 0, target_number = 0;

    // COMMENT : Can we do better than iteration?
    // COMMENT : Currently we pick the first image, this is not intended.
    // Must pick different "image" data everytime.
    for (const auto &batch : *(data_loader))
    {
        auto data = batch.data;
        auto targets = batch.target;

        target_number = targets.template item<int64_t>();

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

    // COMMENT : Trick to simulate a 100% accurate ML model. Perfect AI?
    return target_number == pred_number ? pred_number : target_number;
}

int arr[100] = {
    9, 5, 8, 0, 3, 4, 7, 6, 1, 2,
    12, 15, 18, 19, 16, 10, 11, 14, 17, 13,
    23, 20, 26, 21, 22, 29, 27, 28, 24, 25,
    36, 34, 32, 30, 33, 35, 39, 37, 31, 38,
    41, 48, 45, 43, 46, 42, 44, 47, 49, 40,
    59, 55, 54, 50, 52, 53, 58, 51, 57, 56,
    69, 60, 64, 63, 68, 65, 61, 67, 62, 66,
    75, 70, 79, 73, 71, 74, 72, 76, 78, 77,
    85, 84, 87, 89, 80, 81, 86, 82, 88, 83,
    96, 90, 95, 91, 98, 93, 94, 92, 99, 97};

int main(int argc, const char *argv[])
{

    // variable declarations
    long long int sum;
    long long int n;
    long long int i;
    long long int index;

    char buff[2048];
    memset(buff, '\0', sizeof(buff));

    fptr = fopen("models.txt", "w");
    setvbuf(fptr, buff, _IOLBF, 2048);

    for (;;)
    {
        size_t len;
        const uint8_t *buf;

        HF_ITER(&buf, &len);
        counter++;

        long long int choices = buf[3];
        sum = buf[1];
        index = buf[25];
        i = buf[2];

        // We are working with a constant size arr[100] here.
        n = 100;

        char vars[100];
        memset(vars, '\0', sizeof(vars));
        snprintf(vars, 100, "%s : %lld, %s : %lld, %s : %lld, %s : %lld\n",
                 "sum", sum, "n", n, "i", i, "index", index);

        if (choices > 100)
        {
            //pre-conditions
            assume((preflag == 0));
            sum = 0;
            index = 0;
            i = arr[index];
            precount++;
            precheck(fptr, vars, sum, n, i, index);
        }
        else
        {
            // loop-check program
            assume((loopflag + postflag < 2));
            assume(INV(sum, n, i, index));

            // Loop Condition
            if (index < n)
            {
                // Bounded Unrolling
                int k = UNROLL_LIMIT;
                while ((index < n) && k--)
                {
                    assume((loopflag == 0));
                    // loop body
                    long long int temp_sum = sum;
                    long long int temp_n = n;
                    long long int temp_i = arr[index];
                    long long int temp_index = index;

                    i = arr[index];
                    sum += predict(i);
                    index += 1;

                    loopcount++;
                    loopcheck(fptr, vars, temp_sum, temp_n, temp_i, temp_index, sum, n, i, index);
                }
            }
            else
            {
                // post-check program
                assume((postflag == 0));
                // post-condition
                postcount++;
                postcheck(fptr, vars, (sum == (5 * ((index / 10) - 1) * (index / 10)) + ((index / 10) * (index - 10 * ((index / 10))))), sum, n, arr[index], index)
                // (sum == 450)
            }
        }

        if (preflag + loopflag + postflag == 0 && counter == 50)
        {
            fprintf(fptr, "%s : %lld, %s : %lld, %s : %lld\n",
                    "precount", precount, "loopcount", loopcount, "postcount", postcount);
            counter = 0;
        }

        if (preflag + loopflag + postflag >= 3)
        {
            fclose(fptr);
            assert(0);
        }
    }

    fclose(fptr);
    return 0;
}