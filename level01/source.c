#include <stdio.h>
#include <string.h>

char a_user_name[256];

// Function to verify the username
int verify_user_name(void) {
    // Check the username here
    return strncmp("dat_wil", a_user_name, 7);

}

// Function to verify the user password
int verify_user_pass(const char *password) {
    // Check the password here
      return strncmp("admin", password, 5);

}

int main(void) {
    int result = 1;  // Default result is failure

    char password[100];

    // Initialize the password buffer
    memset(password, 0, sizeof(password));

    puts("********* ADMIN LOGIN PROMPT *********");

    // Get the username
    printf("Enter Username: ");
    fgets(a_user_name, sizeof(a_user_name), stdin);
    a_user_name[strcspn(a_user_name, "\n")] = '\0';  // Remove trailing newline

    // Verify the username
    if (verify_user_name() == 0) {
        // Get the password
        printf("Enter Password: ");
        fgets(password, sizeof(password), stdin);
        password[strcspn(password, "\n")] = '\0';  // Remove trailing newline

        // Verify the password
        if (verify_user_pass(password) == 0) {
            puts("Access granted!\n");
            result = 0;  // Success
        } else {
            puts("Incorrect password...\n");
        }
    } else {
        puts("Incorrect username...\n");
    }

    return result;
}
