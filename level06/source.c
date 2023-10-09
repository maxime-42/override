#include <stdio.h>
#include <stdlib.h>
#include <sys/ptrace.h>
#include <string.h>

// Function to authenticate user login and serial number
int authenticate(char *login, unsigned int serial) {
    size_t loginLength;
    int result;

    // Remove newline character from login string
    loginLength = strcspn(login, "\n");
    login[loginLength] = '\0';

    // Calculate the length of the login string
    loginLength = strnlen(login, 0x20);

    // Check if login length is less than 6 characters
    if ((int)loginLength < 6) {
        result = 1; // Authentication failed
    } else {
        // Check for tampering using ptrace
        long ptraceResult = ptrace(PTRACE_TRACEME);

        if (ptraceResult == -1) {
            // Tampering detected
            puts("\x1b[32m.---------------------------.");
            puts("\x1b[31m| !! TAMPERING DETECTED !!  |");
            puts("\x1b[32m'---------------------------'");
            result = 1; // Authentication failed
        } else {
            // Initialize a hash value
            unsigned int hash = ((int)login[3]) ^ 0x1337U + 0x5eeded;

            // Calculate the hash based on the login string
            for (int i = 0; i < (int)loginLength; i++) {
                if (login[i] < ' ') {
                    return 1; // Authentication failed
                }
                hash = hash + ((int)login[i] ^ hash) % 0x539;
            }

            // Compare the calculated hash with the provided serial
            if (serial == hash) {
                result = 0; // Authentication succeeded
            } else {
                result = 1; // Authentication failed
            }
        }
    }

    return result;
}

int main() {
    int status;
    char loginBuffer[0x20]; // 32 characters
    unsigned int serial;

    puts("***********************************");
    puts("*\t\tlevel06\t\t  *");
    puts("***********************************");

    printf("-> Enter Login: ");
    fgets(loginBuffer, 0x20, stdin);

    puts("***********************************");
    puts("***** NEW ACCOUNT DETECTED ********");
    puts("***********************************");

    printf("-> Enter Serial: ");
    scanf("%u", &serial);

    // Authenticate user based on input
    status = authenticate(loginBuffer, serial);

    if (status == 0) {
        puts("Authenticated!");
        system("/bin/sh");
    }

    return status;
}
