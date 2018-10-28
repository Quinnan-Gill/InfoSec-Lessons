#!/bin/bash

# Every system differs with its system calls so 

# The main file is: /usr/include/x86_64-linux-gnu/asm/unistd_64.h
# The other one is /usr/include/x86_64-linux-gnu/bits/syscall.h

if [ -z $1 ]; then
    echo "Need a grep statemnt to access:"
    echo "/usr/include/x86_64-linux-gnu/asm/unistd_64.h"
    less /usr/include/x86_64-linux-gnu/asm/unistd_64.h
else
    cat /usr/include/x86_64-linux-gnu/asm/unistd_64.h | grep -i $1
fi

# Run `echo -n "#include <sys/syscall.h>\nSYS_read" | gcc -E -` to get the sys files used
