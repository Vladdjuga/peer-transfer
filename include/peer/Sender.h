// Sender.h
// Small header-only class demonstrating the Rule of Five.

#ifndef SENDER_H
#define SENDER_H

#include <cstddef>
#include <algorithm>
#include <utility>
#include <cstring>
#include <string>

class Sender {
private:
    std::string buffer_;
    std::size_t size_;
public:
    // Rule of Five
    Sender(const Sender&) = default;
    Sender(Sender&&) noexcept = default;
    Sender& operator=(const Sender&) = default;
    Sender& operator=(Sender&&) noexcept = default;
    ~Sender() = default;

    Sender() = default;
    explicit Sender(const std::string& buffer)
        : buffer_(buffer), size_(buffer.size()) {}

};

#endif // SENDER_H

