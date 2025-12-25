# PeerTransfer - Simple peer-to-peer file transfer utility
# Repository: https://github.com/Vladdjuga/peer-transfer.git

cmake_minimum_required(VERSION 3.15)
project(PeerTransfer
    VERSION 0.1
    LANGUAGES CXX
    DESCRIPTION "Simple peer-to-peer file transfer utility using Asio"
    HOMEPAGE_URL "https://github.com/Vladdjuga/peer-transfer.git"
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)

# Add FetchContent to download spdlog at configure time and make it available
include(FetchContent)
FetchContent_Declare(
  spdlog
  GIT_REPOSITORY https://github.com/gabime/spdlog.git
  GIT_TAG v1.11.0
)
FetchContent_MakeAvailable(spdlog)

FetchContent_Declare(
        gtest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG release-1.12.1
)
FetchContent_MakeAvailable(gtest)

# Add standalone Asio (header-only, no Boost needed)
FetchContent_Declare(
  asio
  GIT_REPOSITORY https://github.com/chriskohlhoff/asio.git
  GIT_TAG asio-1-28-0
)
FetchContent_MakeAvailable(asio)

# Add Asio include directory
include_directories(${asio_SOURCE_DIR}/asio/include)

file(GLOB SOURCES "src/*.cpp")

add_executable(sender src/main_sender.cpp src/sender.cpp src/utils.cpp
        src/io/file_reader.cpp
        include/io/file_reader.h
        src/io/file_writer.cpp)
add_executable(receiver src/main_receiver.cpp src/receiver.cpp src/utils.cpp
        src/io/file_reader.cpp
        include/io/file_reader.h
        include/io/file_writer.h
        src/io/file_writer.cpp)

# Define ASIO_STANDALONE for standalone Asio (without Boost)
target_compile_definitions(sender PRIVATE ASIO_STANDALONE)
target_compile_definitions(receiver PRIVATE ASIO_STANDALONE)

# Link libraries to executables
target_link_libraries(sender PRIVATE spdlog::spdlog ws2_32)
target_link_libraries(receiver PRIVATE spdlog::spdlog ws2_32)

# Automatically find all test files
file(GLOB TEST_SOURCES "tests/*_test.cpp")

# Create test executable with all test files
add_executable(run_all_tests ${TEST_SOURCES} src/utils.cpp src/sender.cpp src/receiver.cpp
        src/io/file_reader.cpp
        include/io/file_reader.h
        src/io/file_writer.cpp)
target_compile_definitions(run_all_tests PRIVATE ASIO_STANDALONE)
target_link_libraries(run_all_tests PRIVATE gtest gtest_main spdlog::spdlog ws2_32)
target_include_directories(run_all_tests PRIVATE ${gtest_SOURCE_DIR}/include)

# Enable testing
enable_testing()
add_test(NAME AllTests COMMAND run_all_tests)
