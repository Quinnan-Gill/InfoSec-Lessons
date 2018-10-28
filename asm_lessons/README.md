# Running the x86 assembly code.

So in this lesson about I am going to start off with a lesson on bash scripting (what?). Yeah, because in this directory are a couple of files to help run and create assembly (asm) code.

## Display System
Every system is different with different system calls. These system calls are the universal linux commands that have existed forever. If you have ever used the C library <unistd.h> or any of it variants (for 32-bit and 64-bit machines) these are the system calls x86 can use. The problem is FINDING them. It may require a little linux foo to find the unistd.h. It is usually in  the `/usr/include/` directory, but that directory includes alot of `unistd.h` and other directories as well. So run:

`$ echo -n "#include <sys/syscall.h>\nSYS_read" | gcc -E -`

to find the og `unistd.h` file.

The bash script `display_sys.sh` goes to
