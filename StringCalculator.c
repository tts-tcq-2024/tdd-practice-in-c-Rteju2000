#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int add(const char* numbers) {
    if (numbers == NULL || strlen(numbers) == 0) {
        return 0;
    }

    int sum = 0;
    const char* delimiters = ",\n";
    char* input = strdup(numbers);
    char* ptr = input;

    // Check for custom delimiter
    if (input[0] == '/' && input[1] == '/') {
        delimiters = (char[]){input[2], '\0'};
        ptr = strstr(input, "\n") + 1;
    }

    char* token = strtok(ptr, delimiters);
    while (token != NULL) {
        int num = atoi(token);
        if (num <= 1000) {
            sum += num;
        }
        token = strtok(NULL, delimiters);
    }

    free(input);
    return sum;
}
