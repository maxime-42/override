#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct s_message {
    char message[140];
    char username[40];
    int len_message;
};

void secret_backdoor(void) {
    char input[128];

    printf("Enter your command: ");
    fgets(input, sizeof(input), stdin);
    system(input);
}

void set_msg(char *message, struct s_message *msg) {
    char input[1024]; // Increased the buffer size for input
    
    printf("Enter your message: ");
    fgets(input, sizeof(input), stdin);
    
    // Use strncpy to avoid buffer overflow
    strncpy(msg->message, input, sizeof(msg->message) - 1);
    msg->message[sizeof(msg->message) - 1] = '\0'; // Ensure null-terminated string
}

void set_username(struct s_message *msg) {
    char input[128];
    
    printf("Enter your username: ");
    fgets(input, sizeof(input), stdin);

    // Ensure that the username does not exceed the buffer size
    strncpy(msg->username, input, sizeof(msg->username) - 1);
    msg->username[sizeof(msg->username) - 1] = '\0'; // Ensure null-terminated string
    
    printf("Welcome, %s\n", msg->username);
}

void handle_msg(void) {
    struct s_message message;
    memset(&message, 0, sizeof(message)); // Initialize the message structure

    set_username(&message);
    set_msg(message.message, &message);
    
    // Handle the message, not shown in the code
}

int main(void) {
    puts("----------------------------");
    puts("|   ~Welcome to l33t-m$n ~  v1337 |");
    puts("----------------------------");

    handle_msg();
    return 0;
}
