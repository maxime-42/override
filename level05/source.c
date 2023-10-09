#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

int main(void) {
    char input[100];
    int length = 0;

    // Read user input
    fgets(input, sizeof(input), stdin);
    
    length = 0;
    while (true) {
        // Initialize a variable for checking character equality
        char currentChar = input[length];
        
        // Check if the current character is null-terminated
        if (currentChar == '\0') {
            break;
        }
        
        // Check if the character is an uppercase letter
        if ('A' <= currentChar && currentChar <= 'Z') {
            // Convert uppercase to lowercase
            input[length] = currentChar + 32;
        }
        
        length++;
    }

    // Print the modified input
    printf("%s", input);
    
    return 0;
}
