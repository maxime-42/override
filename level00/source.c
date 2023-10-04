#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

bool authenticate(void)
{
    int password;

    // Print a header
    printf("***********************************\n");
    printf("* \t     -Level00 -\t\t  *\n");
    printf("***********************************\n");

    // Prompt for password
    printf("Password: ");
    scanf("%d", &password);

    // Check if the entered password is correct
    if (password != 0x149c) {
        printf("\nInvalid Password!\n");
        return false;
    } else {
        printf("\nAuthenticated!\n");
        // Execute a shell with authenticated access
        system("/bin/sh");
        return true;
    }
}

int main(void)
{
    // Call the authentication function
    bool isAuthSuccessful = authenticate();
    
    // Return 1 if authentication failed, 0 otherwise
    return !isAuthSuccessful;
}
