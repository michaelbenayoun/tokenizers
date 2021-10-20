cmake_minimum_required(VERSION 3.16)
project(tokenizers_cpp_test)

set(CMAKE_CXX_STANDARD 14)

if (NOT TOKENIZERS_LIBRARY_PATH)
    message(FATAL_ERROR "You must specify the path to the tokenizers library")
endif()

set(CARGO_BUILD_TYPE "debug" CACHE STRING "Whether to build tokenizers-cpp in debug or release mode")
set_property(
    CACHE CARGO_BUILD_TYPE
    PROPERTY STRINGS
    "debug" "release"
)

set(CARGO_CONFIG_PATH ${TOKENIZERS_LIBRARY_PATH}/bindings/cpp/.cargo/config.toml)
set(CARGO_MANIFEST_PATH ${TOKENIZERS_LIBRARY_PATH}/bindings/cpp/Cargo.toml)

if(CMAKE_TOOLCHAINE_NAME STREQUAL "aarch64-linux-gnu")
    set(CARGO_TARGET "--target aarch64-unknown-linux-gnu")
    set(CARGO_BUILD_TYPE "aarch64-unknown-linux-gnu/${CARGO_BUILD_TYPE}")
else()
    set(CARGO_TARGET "")
endif()

if(CARGO_BUILD_TYPE MATCHES "debug")
    execute_process(
        COMMAND
        bash -c "cargo build --manifest-path=${CARGO_MANIFEST_PATH} ${CARGO_TARGET}"
    )
else()
    execute_process(
        COMMAND
        bash -c "cargo build --manifest-path=${CARGO_MANIFEST_PATH} ${CARGO_TARGET} --release"
    )
endif()
message(STATUS "Building tokenizers-cpp bindings - done")

execute_process(COMMAND bash "create_symlinks.sh" ${TOKENIZERS_LIBRARY_PATH} ${CARGO_BUILD_TYPE})
message(STATUS "Created symlinks for bindings related libraries")

# Find cxxrust
find_library(CXXBRIDGE_LIBRARY_PATH cxxbridge1 PATH ${TOKENIZERS_LIBRARY_PATH}/bindings/cpp/target/${CARGO_BUILD_TYPE})
message(STATUS "Found cxxbridge: ${CXXBRIDGE_LIBRARY_PATH}")

# Find tokenizers
find_library(TOKENIZERS_RUST_LIBRARY tokenizers PATH ${TOKENIZERS_LIBRARY_PATH}/bindings/cpp/target/${CARGO_BUILD_TYPE})
message(STATUS "Found tokenizers: ${TOKENIZERS_RUST_LIBRARY}")

# Find tokenizers-cpp
find_library(TOKENIZERS_CPP_LIBRARY_PATH tokenizers-cpp PATH ${TOKENIZERS_LIBRARY_PATH}/bindings/cpp/target/${CARGO_BUILD_TYPE})
message(STATUS "Found tokenizers-cpp: ${TOKENIZERS_CPP_LIBRARY_PATH}")


include_directories(
    tokenizers_cpp_test PUBLIC
    ${TOKENIZERS_LIBRARY_PATH}/bindings/cpp
    ${TOKENIZERS_LIBRARY_PATH}/bindings/cpp/target/cxxbridge
    ${TOKENIZERS_LIBRARY_PATH}/bindings/cpp/thirdparty
    ${TOKENIZERS_LIBRARY_PATH}/bindings/cpp/target/${CARGO_BUILD_TYPE}/tokenizers-cpp
)

add_executable(tokenizers_cpp_test main.cpp)

target_link_libraries(
    tokenizers_cpp_test
    ${CXXBRIDGE_LIBRARY_PATH}
    ${TOKENIZERS_RUST_LIBRARY}
    ${TOKENIZERS_CPP_LIBRARY_PATH}
)
