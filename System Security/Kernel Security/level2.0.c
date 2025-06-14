#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#define PROC_FILE "/proc/pwncollege"
#define PASSWORD "hghlqjzerhxumnnf"

int main() {
    int fd;
    ssize_t bytes_written, bytes_read;
    char response[128]; // Buffer to store the response

    // Open the /proc/pwncollege file
    fd = open(PROC_FILE, O_RDWR);
    if (fd < 0) {
        perror("Failed to open " PROC_FILE);
        exit(EXIT_FAILURE);
    }

    // Write the password
    bytes_written = write(fd, PASSWORD, strlen(PASSWORD));
    if (bytes_written < 0) {
        perror("Failed to write password");
        close(fd);
        exit(EXIT_FAILURE);
    }
    printf("[+] Sent password: %s (%zd bytes)\n", PASSWORD, bytes_written);
    close(fd);
    printf("[+] Check the logs the flag will be there \n");
    return 0;
}
