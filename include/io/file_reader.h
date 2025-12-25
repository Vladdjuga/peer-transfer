//
// Created by User on 12/25/2025.
//

#ifndef FILE_READER_H
#define FILE_READER_H
#include <fstream>
#include <string>

// Abstraction for file reading
class IFileReader {
public:
    virtual ~IFileReader() = default;

    virtual bool openFile(const std::string &filePath);
    virtual void closeFile();
    virtual bool eof();
    virtual size_t read(char*& buffer);
};
class BufferedFileReader final : public IFileReader {
private:
    std::ifstream bufferStream;
    std::size_t chunkIndex = 0;
    std::size_t chunkSize = 0;
public:
    BufferedFileReader();
    explicit BufferedFileReader(const std::size_t& chunkIndex, const std::size_t& chunkSize);

    // Rule of Five
    BufferedFileReader(const BufferedFileReader&) = delete;
    BufferedFileReader& operator=(const BufferedFileReader&) = delete;
    BufferedFileReader(BufferedFileReader&&) noexcept;
    BufferedFileReader& operator=(BufferedFileReader&&) noexcept;

    ~BufferedFileReader() override;

    bool openFile(const std::string &filePath) override;
    void closeFile() override;
    bool eof() override;
    size_t read(char*& buffer) override;
};

#endif //FILE_READER_H
