#include <iostream>

int main(const int argc, char* argv[]) {
    if (argc < 3) {
        std::cout << "Usage: ./receiver <PORT> <SAVE_PATH>\n";
        return 1;
    }
    int port = std::stoi(argv[1]);
    std::string savePath = argv[2];
    return 0;
}