// Receiver.h
// Small header-only class demonstrating the Rule of Five.

#ifndef RECEIVER_H
#define RECEIVER_H

#include <string>

class Receiver {
private:
    std::string path_;
public:
    // Rule of Five
    Receiver(const Receiver&) = default;
    Receiver(Receiver&&) noexcept = default;
    Receiver& operator=(const Receiver&) = default;
    Receiver& operator=(Receiver&&) noexcept = default;
    ~Receiver() = default;

    Receiver() = default;
    explicit Receiver(const std::string& path) : path_(path) {}

    const std::string& path() const noexcept { return path_; }
    void setPath(const std::string& path) { path_ = path; }
};

#endif // RECEIVER_H

