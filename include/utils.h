//
// Created by User on 12/22/2025.
//

#ifndef UTILS_H
#define UTILS_H
#include <optional>
#include <string>

std::optional<std::string> readFile(const std::string& filePath);
void writeFile(const std::string& filePath, const std::string& data);

#endif //UTILS_H
