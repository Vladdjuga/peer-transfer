//
// Created by User on 12/22/2025.
//

#include "sender.h"
#include "utils.h"

#include <asio.hpp>
#include <spdlog/spdlog.h>

void sendFile(const std::string& ip, int port, const std::string& path) {
    try {
        spdlog::info("Reading file: {}", path);
        auto fileContent = readFile(path);

        if (!fileContent.has_value()) {
            spdlog::error("Failed to read file: {}", path);
            return;
        }

        spdlog::info("File size: {} bytes", fileContent->size());

        // Create io_context
        asio::io_context io_context;

        // Resolve the server endpoint
        asio::ip::tcp::resolver resolver(io_context);
        auto endpoints = resolver.resolve(ip, std::to_string(port));

        // Create and connect socket
        asio::ip::tcp::socket socket(io_context);
        spdlog::info("Connecting to {}:{}...", ip, port);
        asio::connect(socket, endpoints);
        spdlog::info("Connected successfully");

        // Send file size first (8 bytes)
        uint64_t fileSize = fileContent->size();
        asio::write(socket, asio::buffer(&fileSize, sizeof(fileSize)));

        // Send file content
        spdlog::info("Sending file data...");
        asio::write(socket, asio::buffer(*fileContent));

        spdlog::info("File sent successfully: {} bytes", fileSize);

    } catch (std::exception& e) {
        spdlog::error("Error sending file: {}", e.what());
    }
}


