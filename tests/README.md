# Testing Structure

## Overview
This project uses Google Test (gtest) for unit testing. Each header file in `include/` has a corresponding test file in `tests/`.

## Test Files
- **tests/utils_test.cpp** - Tests for utils.h functions (file I/O operations)
- **tests/sender_test.cpp** - Tests for sender.h functionality
- **tests/receiver_test.cpp** - Tests for receiver.h functionality

## How to Add New Tests

### 1. Create a new test file
When you add a new header file, create a corresponding test file following the naming convention:
```
include/mymodule.h  →  tests/mymodule_test.cpp
```

### 2. Test file template
```cpp
#include "mymodule.h"
#include <gtest/gtest.h>

TEST(MyModuleTest, TestName) {
    // Arrange
    // ... setup test data
    
    // Act
    // ... call function being tested
    
    // Assert
    EXPECT_EQ(expected, actual);
}
```

### 3. Automatic discovery
The CMakeLists.txt automatically finds all `*_test.cpp` files in the `tests/` directory using:
```cmake
file(GLOB TEST_SOURCES "tests/*_test.cpp")
```

No need to manually add test files to CMakeLists.txt!

## Running Tests

### From CLion
1. Rebuild the project (Ctrl+F9)
2. Run the `run_all_tests` configuration
3. View test results in the Run window

### From Command Line
```bash
cd cmake-build-debug
ctest --output-on-failure
```

Or run the test executable directly:
```bash
./run_all_tests
```

## Test Naming Conventions
- Test file: `<module>_test.cpp`
- Test suite: `<Module>Test`
- Test case: Descriptive name using PascalCase

Example:
```cpp
TEST(FileUtilsTest, ReadExistingFile) {
    // test implementation
}
```

