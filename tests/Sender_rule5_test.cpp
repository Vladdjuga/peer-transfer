#include <gtest/gtest.h>
#include "peer/Sender.h"
#include <string>

using namespace peer;

TEST(SenderRule5Test, DefaultConstructor) {
    Sender s;
    EXPECT_EQ(s.size(), 0);
    EXPECT_EQ(s.data(), nullptr);
}

TEST(SenderRule5Test, ParameterizedConstructor) {
    const char* data = "hello";
    Sender s(data, 5);
    EXPECT_EQ(s.size(), 5);
    EXPECT_NE(s.data(), nullptr);
    EXPECT_EQ(std::string(s.data(), s.size()), "hello");
}

TEST(SenderRule5Test, CopyConstructor) {
    const char* data = "copy me";
    Sender s1(data, 7);
    Sender s2(s1);

    EXPECT_EQ(s1.size(), 7);
    EXPECT_EQ(s2.size(), 7);
    EXPECT_NE(s1.data(), s2.data()); // Deep copy
    EXPECT_EQ(std::string(s2.data(), s2.size()), "copy me");
}

TEST(SenderRule5Test, MoveConstructor) {
    const char* data = "move me";
    Sender s1(data, 7);
    const char* original_ptr = s1.data();

    Sender s2(std::move(s1));

    EXPECT_EQ(s2.size(), 7);
    EXPECT_EQ(s2.data(), original_ptr); // Pointer stolen

    EXPECT_EQ(s1.size(), 0);
    EXPECT_EQ(s1.data(), nullptr);
}

TEST(SenderRule5Test, CopyAssignment) {
    Sender s1("data1", 5);
    Sender s2("data2", 5);

    s2 = s1;

    EXPECT_EQ(s2.size(), 5);
    EXPECT_EQ(std::string(s2.data(), 5), "data1");
    EXPECT_NE(s1.data(), s2.data());
}

TEST(SenderRule5Test, MoveAssignment) {
    Sender s1("move", 4);
    Sender s2("dest", 4);
    const char* original_ptr = s1.data();

    s2 = std::move(s1);

    EXPECT_EQ(s2.size(), 4);
    EXPECT_EQ(s2.data(), original_ptr);

    EXPECT_EQ(s1.size(), 0);
    EXPECT_EQ(s1.data(), nullptr);
}

