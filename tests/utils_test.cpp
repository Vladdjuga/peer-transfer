//
// Created by User on 12/22/2025.
//

#include "utils.h"

#include <fstream>
#include <gtest/gtest.h>


TEST(FileUtilsTest, ReadExistingFile) {
    const std::string testFilePath = "test_existing_file.txt";
    const std::string testContent = "Hello, World!";

    // Create a test file with known content
    std::ofstream(testFilePath) << testContent;

    const auto result = readFile(testFilePath);
    ASSERT_TRUE(result.has_value());
    EXPECT_EQ(result.value(), testContent);

    // Clean up
    std::remove(testFilePath.c_str());
}

TEST(FileUtilsTest, ReadNonExistingFile) {
    const std::string testFilePath = "non_existing_file_xyz123.txt";

    const auto result = readFile(testFilePath);
    EXPECT_FALSE(result.has_value());
}

TEST(FileUtilsTest, WriteAndReadFile) {
    const std::string testFilePath = "test_write_file.txt";
    const std::string testContent = "Test data for write operation";

    // Write content to file
    writeFile(testFilePath, testContent);

    // Read it back
    const auto result = readFile(testFilePath);
    ASSERT_TRUE(result.has_value());
    EXPECT_EQ(result.value(), testContent);

    // Clean up
    std::remove(testFilePath.c_str());
}

TEST(FileUtilsTest, WriteEmptyFile) {
    const std::string testFilePath = "test_empty_file.txt";
    const std::string testContent;

    // Write empty content
    writeFile(testFilePath, testContent);

    // Read it back
    const auto result = readFile(testFilePath);
    ASSERT_TRUE(result.has_value());
    EXPECT_EQ(result.value(), testContent);

    // Clean up
    std::remove(testFilePath.c_str());
}

TEST(FileUtilsTest, WriteMultiRowTextToFile) {
    const std::string testFilePath = "test_empty_file.txt";
    const std::string testContent="Line 1\nLine 2\nLine 3\nLine 4\nLine 5";

    // Write empty content
    writeFile(testFilePath, testContent);

    // Read it back
    const auto result = readFile(testFilePath);
    ASSERT_TRUE(result.has_value());
    EXPECT_EQ(result.value(), testContent);

    // Clean up
    std::remove(testFilePath.c_str());
}



