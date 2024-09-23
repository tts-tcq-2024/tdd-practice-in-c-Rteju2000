#include <stdlib.h>
#include <string.h>
#include <stdio.h>
 
// function to convert a string to an integer
static int stringToInteger(const char* str) {
    return atoi(str);
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
    char* inputCopy = strdup(input);  
    char* token = strtok(inputCopy, delimiters);
    while (token != NULL) {
        int number = stringToInteger(token); 
        accumulateNegatives(number, negatives); 
        sum += isValidNumber(number); 
        token = strtok(NULL, delimiters); 
    }
    free(inputCopy);
    // If any negatives were found, format the message and give an exception
    if (strlen(negatives) > 0) {
        negatives[strlen(negatives) - 1] = '\0';
        fprintf(stderr, "Negatives not allowed\n", negatives);
        exit(EXIT_FAILURE); 
    }
    return sum;
}
 
// function to detect and handle custom delimiters
static const char* extractCustomDelimiter(const char* input, char* delimiters) {
    if (input[0] == '/' && input[1] == '/') {
        // Custom delimiter found, get the delimiter character after "//" and before "\n"
        delimiters[0] = input[2];  
        delimiters[1] = '\n';     
        delimiters[2] = '\0';    
        return strchr(input, '\n') + 1; 
    }
    // If no custom delimiter is found, use comma and newline as default
    strcpy(delimiters, ",\n");
    return input; 
}
 
static int add(const char* input) {
    // If input is NULL or an empty string, return 0
    if (input == NULL || *input == '\0') {
        return 0;
    }
    char delimiters[3];  
    char negatives[256] = {0};  
    const char* numbersPart = extractCustomDelimiter(input, delimiters);
    return sumNumbers(numbersPart, delimiters, negatives);
}
