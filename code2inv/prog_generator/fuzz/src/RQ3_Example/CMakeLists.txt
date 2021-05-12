cmake_minimum_required(VERSION 3.0 FATAL_ERROR)
project(mnist_example)

find_package(Torch REQUIRED)

add_executable(mnist_example mnist_example.cpp)
target_link_libraries(mnist_example "${TORCH_LIBRARIES}")
set_property(TARGET mnist_example PROPERTY CXX_STANDARD 17)