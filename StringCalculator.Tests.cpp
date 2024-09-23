#include <gtest/gtest.h>
#include "StringCalculator.h"  // Your add function should be declared here

// Test for empty input
TEST(StringCalculatorTests, ExpectZeroForEmptyInput) {
    const char* input = "";
    int expected = 0;
    int result = add(input);
    ASSERT_EQ(result, expected);
}

// Test for single zero input
TEST(StringCalculatorTests, ExpectZeroForSingleZero) {
    const char* input = "0";
    int expected = 0;
    int result = add(input);
    ASSERT_EQ(result, expected);
}

// Test for the sum of two numbers
TEST(StringCalculatorTests, ExpectSumForTwoNumbers) {
    const char* input = "1,2";
    int expected = 3;
    int result = add(input);
    ASSERT_EQ(result, expected);
}

// Test to ignore numbers greater than 1000
TEST(StringCalculatorTests, IgnoreNumbersGreaterThan1000) {
    const char* input = "1,1001";
    int expected = 1;
    int result = add(input);
    ASSERT_EQ(result, expected);
}

// Test for sum with custom delimiter
TEST(StringCalculatorTests, ExpectSumWithCustomDelimiter) {
    const char* input = "//;\n1;2";
    int expected = 3;
    int result = add(input);
    ASSERT_EQ(result, expected);
}

// Test for sum with newline delimiter
TEST(StringCalculatorTests, ExpectSumWithNewlineDelimiter) {
    const char* input = "1\n2,3";
    int expected = 6;
    int result = add(input);
    ASSERT_EQ(result, expected);
}

// Test for handling negative numbers, expecting exception or error
TEST(StringCalculatorTests, NegativeNumbersRaiseException) {
    const char* input = "1,-2,-3";
    char error_message[256] = {0};  // Buffer for error message

    int result = add(input, error_message);

    ASSERT_EQ(result, -1);  // Check if an error occurred
    ASSERT_STREQ(error_message, "Negative numbers not allowed: -2 -3");  // Check the error message
}


int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
