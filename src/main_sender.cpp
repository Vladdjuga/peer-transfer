//
// Created by User on 12/22/2025.
//

#include "sender.h"
#include <spdlog/spdlog.h>

int main(const int argc, char* argv[]) {
    spdlog::info("Sender started");

    if (argc < 4) {
        spdlog::error("Usage: sender <IP> <PORT> <FILE_PATH>");
        spdlog::info("Example: sender 127.0.0.1 8080 file.txt");
        return 1;
    }

    const std::string ip = argv[1];
    const int port = std::stoi(argv[2]);
    const std::string filePath = argv[3];

    sendFile(ip, port, filePath);

    return 0;
}
