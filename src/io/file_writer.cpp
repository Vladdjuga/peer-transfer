//
// Created by User on 12/25/2025.
//

#include "io/file_writer.h"

// Constructors, destructors
BufferedFileWriter::BufferedFileWriter() = default;
BufferedFileWriter::BufferedFileWriter(BufferedFileWriter&&) noexcept = default;
BufferedFileWriter& BufferedFileWriter::operator=(BufferedFileWriter&&) noexcept = default;
BufferedFileWriter::~BufferedFileWriter() { BufferedFileWriter::closeFile(); }

BufferedFileWriter::BufferedFileWriter(const std::size_t& chunkIndex, const std::size_t& chunkSize)
    : chunkIndex(chunkIndex), chunkSize(chunkSize) {}

// Methods
bool BufferedFileWriter::openFile(const std::string &filePath) {
    bufferStream = std::ofstream(filePath, std::ios::out | std::ios::binary);
    return bufferStream.is_open();
}
void BufferedFileWriter::closeFile() {
    bufferStream.close();
}
size_t BufferedFileWriter::write(char* buffer) {
    const std::streamoff offset = static_cast<std::streamoff>(chunkIndex) * static_cast<std::streamoff>(chunkSize);
    bufferStream.seekp(offset, std::ios::beg);
    bufferStream.write(buffer, static_cast<std::streamsize>(chunkSize));
    return bufferStream.tellp();
}