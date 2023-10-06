#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
    char username_buffer[100];
    char password_buffer[42];
    char stored_password[100];
    int read_ret;

    // Initialize buffers to zero
    memset(username_buffer, 0, sizeof(username_buffer));
    memset(password_buffer, 0, sizeof(password_buffer));
    memset(stored_password, 0, sizeof(stored_password));

    FILE *password_file = fopen("/home/users/level03/.pass", "r");
    
    if (password_file == NULL) {
        fprintf(stderr, "ERROR: failed to open password file\n");
        exit(1);
    }

    read_ret = fread(stored_password, 1, sizeof(stored_password), password_file);
    
    // Remove newline character from stored_password
    size_t newline_index = strcspn(stored_password, "\n");
    stored_password[newline_index] = '\0';

    if (read_ret != 0x29) {
        fprintf(stderr, "ERROR: failed to read password file\n");
        fclose(password_file);
        exit(1);
    }

    fclose(password_file);

    puts("===== [ Secure Access System v1.0 ] =====");
    puts("/***************************************\\");
    puts("| You must login to access this system. |");
    puts("\\**************************************/");
    
    printf("--[ Username: ");
    fgets(username_buffer, sizeof(username_buffer), stdin);

    // Remove newline character from username_buffer
    newline_index = strcspn(username_buffer, "\n");
    username_buffer[newline_index] = '\0';

    printf("--[ Password: ");
    fgets(password_buffer, sizeof(password_buffer), stdin);

    // Remove newline character from password_buffer
    newline_index = strcspn(password_buffer, "\n");
    password_buffer[newline_index] = '\0';

    puts("*****************************************");

    int comparison_result = strncmp(stored_password, password_buffer, 0x29);

    if (comparison_result == 0) {
        printf("Greetings, %s!\n", username_buffer);
        system("/bin/sh");
        return 0;
    } else {
        printf("%s does not have access!\n", username_buffer);
        exit(1);
    }
}
