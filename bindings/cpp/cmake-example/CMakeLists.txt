cmake_minimum_required(VERSION 3.16)
project(tokenizers_cpp_test)

set(CMAKE_CXX_STANDARD 14)

## Find cxxrust
find_library(CXXBRIDGE_LIBRARY_PATH cxxbridge1 PATH $ENV{TOKENIZERS_LIBRARY_PATH}/bindings/cpp/target/debug)
message(STATUS "Found cxxbridge: ${CXXBRIDGE_LIBRARY_PATH}")

# Find tokenizers
find_library(TOKENIZERS_RUST_LIBRARY tokenizers PATH $ENV{TOKENIZERS_LIBRARY_PATH}/bindings/cpp/target/debug)
message(STATUS "Found tokenizers: ${TOKENIZERS_RUST_LIBRARY}")

# Find tokenizers-cpp
find_library(TOKENIZERS_CPP_LIBRARY_PATH tokenizers-cpp PATH $ENV{TOKENIZERS_LIBRARY_PATH}/bindings/cpp/target/debug)
message(STATUS "Found tokenizers-cpp: ${TOKENIZERS_CPP_LIBRARY_PATH}")


include_directories(
    tokenizers_cpp_test PUBLIC
    $ENV{TOKENIZERS_LIBRARY_PATH}/bindings/cpp
    $ENV{TOKENIZERS_LIBRARY_PATH}/bindings/cpp/target/cxxbridge
    $ENV{TOKENIZERS_LIBRARY_PATH}/bindings//cpp/thirdparty
    $ENV{TOKENIZERS_LIBRARY_PATH}/bindings/cpp/target/debug/tokenizers-cpp
)


add_executable(tokenizers_cpp_test main.cpp)

target_link_libraries(
    tokenizers_cpp_test
    ${CXXBRIDGE_LIBRARY_PATH}
    ${TOKENIZERS_RUST_LIBRARY}
    ${TOKENIZERS_CPP_LIBRARY_PATH}
)
