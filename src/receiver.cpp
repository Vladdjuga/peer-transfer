//
// Created by User on 12/22/2025.
//

#include "receiver.h"
#include "utils.h"

#include <asio.hpp>
#include <spdlog/spdlog.h>
#include <vector>

void receiveFile(int port, const std::string& savePath) {
    try {
        asio::io_context io_context;

        // Create acceptor to listen for connections
        asio::ip::tcp::acceptor acceptor(io_context, asio::ip::tcp::endpoint(asio::ip::tcp::v4(), port));
        spdlog::info("Listening on port {}...", port);

        // Accept connection
        asio::ip::tcp::socket socket(io_context);
        acceptor.accept(socket);
        spdlog::info("Client connected from {}", socket.remote_endpoint().address().to_string());

        // Receive file size first (8 bytes)
        uint64_t fileSize = 0;
        asio::read(socket, asio::buffer(&fileSize, sizeof(fileSize)));
        spdlog::info("Receiving file: {} bytes", fileSize);

        // Receive file content
        std::vector<char> buffer(fileSize);
        asio::read(socket, asio::buffer(buffer));

        // Convert to string and write to file
        std::string fileContent(buffer.begin(), buffer.end());
        writeFile(savePath, fileContent);

        spdlog::info("File received and saved to: {}", savePath);

    } catch (std::exception& e) {
        spdlog::error("Error receiving file: {}", e.what());
    }
}

