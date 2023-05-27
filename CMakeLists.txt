cmake_minimum_required(VERSION 3.9.1)

project(Huffman
        VERSION 1.0.0
        DESCRIPTION "Huffman codec"
        LANGUAGES CXX)

# Compiler flags
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")

# Path to the executable file
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})

# Create the encoder executable
add_executable(Encoder src/Encoder.cpp src/Heap.cpp src/Huffman.cpp)
target_include_directories(Encoder PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)

# Create the decoder executable
add_executable(Decoder src/Decoder.cpp src/Heap.cpp src/Huffman.cpp)
target_include_directories(Decoder PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)

# Create the Mean Square Error executable
add_executable(MSE src/MSE.cpp)
