cmake_minimum_required(VERSION 3.16)
project(tokenizers_cpp_test)

set(CMAKE_CXX_STANDARD 14)


set(TOKENIZERS_LIBRARY_PATH $ENV{TOKENIZERS_LIBRARY_PATH})
set(CMAKE_BUILD_TYPE "debug")

# execute_process(
#     COMMAND
#     bash -c "cargo build --manifest-path=${TOKENIZERS_LIBRARY_PATH}/Cargo.toml"
# )
# message(STATUS "Building tokenizers")

execute_process(COMMAND bash "create_symlinks.sh" ${TOKENIZERS_LIBRARY_PATH} ${CMAKE_BUILD_TYPE})

# Find cxxrust
find_library(CXXBRIDGE_LIBRARY_PATH cxxbridge1 PATH ${TOKENIZERS_LIBRARY_PATH}/bindings/cpp/target/${CMAKE_BUILD_TYPE})
message(STATUS "Found cxxbridge: ${CXXBRIDGE_LIBRARY_PATH}")

# Find tokenizers
find_library(TOKENIZERS_RUST_LIBRARY tokenizers PATH ${TOKENIZERS_LIBRARY_PATH}/bindings/cpp/target/${CMAKE_BUILD_TYPE})
message(STATUS "Found tokenizers: ${TOKENIZERS_RUST_LIBRARY}")

# Find tokenizers-cpp
find_library(TOKENIZERS_CPP_LIBRARY_PATH tokenizers-cpp PATH ${TOKENIZERS_LIBRARY_PATH}/bindings/cpp/target/${CMAKE_BUILD_TYPE})
message(STATUS "Found tokenizers-cpp: ${TOKENIZERS_CPP_LIBRARY_PATH}")


include_directories(
    tokenizers_cpp_test PUBLIC
    ${TOKENIZERS_LIBRARY_PATH}/bindings/cpp
    ${TOKENIZERS_LIBRARY_PATH}/bindings/cpp/target/cxxbridge
    ${TOKENIZERS_LIBRARY_PATH}/bindings/cpp/thirdparty
    ${TOKENIZERS_LIBRARY_PATH}/bindings/cpp/target/${CMAKE_BUILD_TYPE}/tokenizers-cpp
)

add_executable(tokenizers_cpp_test main.cpp)

target_link_libraries(
    tokenizers_cpp_test
    ${CXXBRIDGE_LIBRARY_PATH}
    ${TOKENIZERS_RUST_LIBRARY}
    ${TOKENIZERS_CPP_LIBRARY_PATH}
)
