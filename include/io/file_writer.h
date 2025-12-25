//
// Created by User on 12/25/2025.
//

#ifndef FILE_WRITER_H
#define FILE_WRITER_H
#include <fstream>
#include <string>

// Abstraction for file writing
class IFileWriter {
public:
    virtual ~IFileWriter() = default;

    virtual bool openFile(const std::string &filePath);
    virtual void closeFile();
    virtual size_t write(char* buffer);
};

class BufferedFileWriter final : public IFileWriter {
private:
    std::ofstream bufferStream;
    std::size_t chunkIndex = 0;
    std::size_t chunkSize = 0;
public:
    BufferedFileWriter();
    explicit BufferedFileWriter(const std::size_t& chunkIndex, const std::size_t& chunkSize);

    // Rule of Five
    BufferedFileWriter(const BufferedFileWriter&) = delete;
    BufferedFileWriter& operator=(const BufferedFileWriter&) = delete;
    BufferedFileWriter(BufferedFileWriter&&) noexcept;
    BufferedFileWriter& operator=(BufferedFileWriter&&) noexcept;

    ~BufferedFileWriter() override;

    bool openFile(const std::string &filePath) override;
    void closeFile() override;
    size_t write(char* buffer) override;
};


#endif //FILE_WRITER_H
