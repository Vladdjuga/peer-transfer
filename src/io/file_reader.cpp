//
// Created by User on 12/25/2025.
//

#include "io/file_reader.h"

// Constructors, destructors
BufferedFileReader::BufferedFileReader() = default;
BufferedFileReader::BufferedFileReader(BufferedFileReader&&) noexcept = default;
BufferedFileReader& BufferedFileReader::operator=(BufferedFileReader&&) noexcept = default;
BufferedFileReader::~BufferedFileReader() { BufferedFileReader::closeFile(); }

BufferedFileReader::BufferedFileReader(const std::size_t& chunkIndex, const std::size_t& chunkSize)
    : chunkIndex(chunkIndex), chunkSize(chunkSize) {}

// Methods
bool BufferedFileReader::openFile(const std::string &filePath) {
    bufferStream = std::ifstream(filePath, std::ios::in | std::ios::binary);
    return bufferStream.is_open();
}

void BufferedFileReader::closeFile() {
    bufferStream.close();
}

bool BufferedFileReader::eof() {
    return bufferStream.eof();
}

size_t BufferedFileReader::read(char*& buffer) {
    const std::streamoff offset = static_cast<std::streamoff>(chunkIndex) * static_cast<std::streamoff>(chunkSize);
    bufferStream.seekg(offset, std::ios::beg);
    bufferStream.read(buffer, static_cast<std::streamsize>(chunkSize));
    return bufferStream.tellg();
}