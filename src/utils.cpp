//
// Created by User on 12/22/2025.
//

#include "utils.h"

#include <fstream>
#include <optional>
#include <string>
#include <spdlog/spdlog.h>


std::optional<std::string> readFile(const std::string& filePath) {
    try {
        if (std::ifstream file(filePath); file) {
            // Read the entire file content into a string
            const std::istreambuf_iterator begin(file);
            const std::istreambuf_iterator<char> end;

            // Construct string from the file content
            std::string content(begin, end);

            spdlog::info("Gathered from file {} this content : {}", filePath,content);

            return content;
        }
        return std::nullopt;
    }catch (std::exception& e) {
        spdlog::error("Exception occurred: {}", e.what());
        return std::nullopt;
    }
}

void writeFile(const std::string& filePath, const std::string& data) {
    try {
        std::ofstream file(filePath);
        file << data;
    }catch (std::exception& e) {
        spdlog::error("Exception occurred: {}", e.what());
    }
}