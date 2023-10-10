#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

// Function to log messages
void log_wrapper(FILE *file, char *prefix, char *message) {
    char buffer[255]; // Maximum log message size

    // Copy the prefix to the buffer
    strcpy(buffer, prefix);

    // Append the message to the buffer, taking care not to exceed its size
    snprintf(buffer + strlen(buffer), sizeof(buffer) - 1 - strlen(buffer), message);

    // Remove newline characters from the buffer
    buffer[strcspn(buffer, "\n")] = '\0';

    // Write the formatted log message to the specified file
    fprintf(file, "LOG: %s\n", buffer);
}

int main(int argc, char *argv[]) {
    char c;
    int fd;
    FILE *log_file, *origin;
    
    // Check for the correct number of command-line arguments
    if (argc != 2) {
        printf("Usage: %s filename\n", argv[0]);
        exit(1);
    }

    // Open the log file for writing
    log_file = fopen("./backups/.log", "w");
    if (log_file == NULL) {
        printf("ERROR: Failed to open %s\n", "./backups/.log");
        exit(1);
    }

    // Log the start of the backup process
    log_wrapper(log_file, "Starting back up: ", argv[1]);

    // Open the specified file for reading
    origin = fopen(argv[1], "r");
    if (origin == NULL) {
        printf("ERROR: Failed to open %s\n", argv[1]);
        exit(1);
    }

    // Create a backup file path
    char backup_path[100];
    strcpy(backup_path, "./backups/");
    strncat(backup_path, argv[1], sizeof(backup_path) - 1 - strlen(backup_path));

    // Open or create the backup file for writing
    fd = open(backup_path, O_CREAT | O_WRONLY | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH);
    if (fd < 0) {
        printf("ERROR: Failed to open %s%s\n", "./backups/", argv[1]);
        exit(1);
    }

    // Copy the contents of the original file to the backup file
    while ((c = fgetc(origin)) != EOF) {
        write(fd, &c, 1);
    }

    // Log the completion of the backup process
    log_wrapper(log_file, "Finished back up ", argv[1]);

    // Close the open files
    fclose(origin);
    close(fd);

    return 0;
}
