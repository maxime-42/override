#include <stdio.h>
#include <stdbool.h>
#include <string.h>

void prog_timeout(void)
{
    // Placeholder for system call
}

unsigned int get_unum(void)
{
    unsigned int input = 0;
    
    fflush(stdout);
    scanf("%u", &input);
    while(getchar() != '\n'); // Clear the input buffer
    return input;
}

void clear_stdin(void)
{
    while(getchar() != '\n'); // Clear the input buffer
}

unsigned int read_number(int* buffer)
{
    unsigned int index = 0;
    
    printf(" Index: ");
    index = get_unum();
    printf(" Number at data[%u] is %u\n", index, buffer[index]);
    return 0;
}

unsigned int store_number(int* buffer)
{
    unsigned int number = 0;
    unsigned int index = 0;
    
    printf(" Number: ");
    number = get_unum();
    printf(" Index: ");
    index = get_unum();
    
    if ((index % 3 == 0) || (number >> 24 != 0xb7)) {
        puts(" *** ERROR! ***");
        puts("   This index is reserved for wil!");
        puts(" *** ERROR! ***");
        return 1;
    }
    buffer[index] = number;
    return 0;
}

int main(int argc, char* argv[], char* envp[])
{
    int buffer[100] = { 0 };
    bool terminate = false;
    
    for (int i = 0; i < argc; i++) {
        memset(argv[i], 0, strlen(argv[i]));
    }
    for (int i = 0; envp[i] != NULL; i++) {
        memset(envp[i], 0, strlen(envp[i]));
    }

    puts("----------------------------------------------------\n"
         "   Welcome to wil's crappy number storage service!    \n"
         "----------------------------------------------------\n"
         " Commands:                                          \n"
         "    store - store a number into the data storage    \n"
         "    read  - read a number from the data storage     \n"
         "    quit  - exit the program                        \n"
         "----------------------------------------------------\n"
         "   wil has reserved some storage :>                 \n"
         "----------------------------------------------------\n");

    while (!terminate) {
        printf("Input command: ");
        char command[20];
        fgets(command, sizeof(command), stdin);
        command[strlen(command) - 1] = '\0';

        if (strcmp(command, "store") == 0) {
            terminate = store_number(buffer);
        } else if (strcmp(command, "read") == 0) {
            read_number(buffer);
        } else if (strcmp(command, "quit") == 0) {
            terminate = true;
        } else {
            printf("Unknown command: %s\n", command);
        }
    }

    return 0;
}
