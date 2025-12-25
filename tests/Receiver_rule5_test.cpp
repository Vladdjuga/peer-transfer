#include <gtest/gtest.h>
#include "peer/Receiver.h"
#include <string>

using namespace peer;

TEST(ReceiverRule5Test, DefaultConstructor) {
    Receiver r;
    EXPECT_EQ(r.path(), nullptr);
}

TEST(ReceiverRule5Test, ParameterizedConstructor) {
    const char* path = "/tmp/file";
    Receiver r(path);
    EXPECT_NE(r.path(), nullptr);
    EXPECT_STREQ(r.path(), path);
}

TEST(ReceiverRule5Test, CopyConstructor) {
    const char* path = "/tmp/copy";
    Receiver r1(path);
    Receiver r2(r1);

    EXPECT_STREQ(r1.path(), path);
    EXPECT_STREQ(r2.path(), path);
    EXPECT_NE(r1.path(), r2.path()); // Deep copy
}

TEST(ReceiverRule5Test, MoveConstructor) {
    const char* path = "/tmp/move";
    Receiver r1(path);
    const char* original_ptr = r1.path();

    Receiver r2(std::move(r1));

    EXPECT_STREQ(r2.path(), path);
    EXPECT_EQ(r2.path(), original_ptr); // Pointer stolen

    EXPECT_EQ(r1.path(), nullptr);
}

TEST(ReceiverRule5Test, CopyAssignment) {
    Receiver r1("/tmp/1");
    Receiver r2("/tmp/2");

    r2 = r1;

    EXPECT_STREQ(r2.path(), "/tmp/1");
    EXPECT_NE(r1.path(), r2.path());
}

TEST(ReceiverRule5Test, MoveAssignment) {
    Receiver r1("/tmp/move");
    Receiver r2("/tmp/dest");
    const char* original_ptr = r1.path();

    r2 = std::move(r1);

    EXPECT_STREQ(r2.path(), "/tmp/move");
    EXPECT_EQ(r2.path(), original_ptr);

    EXPECT_EQ(r1.path(), nullptr);
}

