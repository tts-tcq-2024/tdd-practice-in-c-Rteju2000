#include <stdlib.h>
#include <string.h>
#include <stdio.h>
 
// function to convert a string to an integer
static int stringToInteger(const char* str) {
    return atoi(str);  // Converts string to integer
}
 
// function to check if the number is <= 1000
static int isValidNumber(int number) {
    return (number <= 1000) ? number : 0;
}
 
// function to accumulate negative numbers in a buffer
static void accumulateNegatives(int number, char* negatives) {
    if (number < 0) {
        snprintf(negatives + strlen(negatives), 256 - strlen(negatives), "%d ", number);
    }
}
 
// function to sum numbers from the input
static int sumNumbers(const char* input, const char* delimiters, char* negatives) {
    int sum = 0;
    char* inputCopy = strdup(input);  // Duplicate the input string
    char* token = strtok(inputCopy, delimiters);  // Tokenize using the delimiters
    while (token != NULL) {
        int number = stringToInteger(token);  // Convert token to integer
        accumulateNegatives(number, negatives);  // Collect negatives
        sum += isValidNumber(number);  // Add valid numbers to the sum
        token = strtok(NULL, delimiters);  // Move to the next token
    }
    free(inputCopy);  // Free the duplicated string
 
    // If any negatives were found, return an error code
    if (strlen(negatives) > 0) {
        return -1;  // Return an error code to indicate negative numbers
    }
    return sum;
}
 
// function to detect and handle custom delimiters
static const char* extractCustomDelimiter(const char* input, char* delimiters) {
    if (input[0] == '/' && input[1] == '/') {
        delimiters[0] = input[2];  // Custom delimiter found after "//"
        delimiters[1] = '\n';  // Newline is always a delimiter
        delimiters[2] = '\0';  // Null-terminate the string
        return strchr(input, '\n') + 1;  // Return the part after the custom delimiter
    }
    // Default delimiters: comma and newline
    strcpy(delimiters, ",\n");
    return input;  // Return input if no custom delimiter is found
}
 
// Main add function
int add(const char* input, char* error_message) {
    // Return 0 for empty input
    if (input == NULL || *input == '\0') {
        return 0;
    }
 
    char delimiters[3];  // Buffer to store delimiters
    char negatives[256] = {0};  // Buffer to accumulate negative numbers
 
    const char* numbersPart = extractCustomDelimiter(input, delimiters);  // Handle custom delimiter
    int result = sumNumbers(numbersPart, delimiters, negatives);  // Sum the numbers
 
    // If there are negatives, populate the error message and return -1
    if (result == -1) {
        snprintf(error_message, 256, "Negatives not allowed: %s", negatives);
        return -1;  // Return error code to indicate failure
    }
 
    return result;
}
