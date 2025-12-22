//
// Created by User on 12/22/2025.
//

#include "receiver.h"
#include <spdlog/spdlog.h>

int main(int argc, char* argv[]) {
    spdlog::info("Receiver started");

    if (argc < 3) {
        spdlog::error("Usage: receiver <PORT> <SAVE_PATH>");
        spdlog::info("Example: receiver 8080 received_file.txt");
        return 1;
    }

    int port = std::stoi(argv[1]);
    std::string savePath = argv[2];

    receiveFile(port, savePath);

    return 0;
}
