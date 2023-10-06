#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdint.h>
#include <string.h>


int decrypt(int rot ) {
    char key[] = "Q}|u`sfg~sf{}|a3";
    int result;

    for (int i = 0; key[i] != '\0'; i++) {
        char decrypted_char = key[i] ^ rot; // Perform XOR decryption
        key[i] = decrypted_char;
    }

    if (!strncmp(key, "Congratulations!", 0x11) ) {
        system("/bin/sh"); // Execute shell if the key matches
    } else {
        printf("\nInvalid Password\n");
    }

    return result;
}



void test(int user_input, int expected_value) {
    int difference = expected_value - user_input;
    
    switch (difference) {

        case 1 ... 21: // Differences 1-15
            decrypt(difference);
            break;
        default:
            decrypt(rand()); // Use random value for decryption
            break;	    
    }
}

int main(void) {
    uint32_t seed = time(NULL);
    srand(seed);
    
    printf("***********************************\n");
    printf("*\t\tlevel03\t\t**\n");
    printf("***********************************\n");
    
    printf("Password:");
    int user_password;
    scanf("%d", &user_password);
    
    test(user_password, 0x1337d00d);
    
    return 0;
}
