#!/bin/bash
# ^^^ For bash scripts it is imporant to start off with a shabang (#!) then
# use /bin/bash to indecate the what file it is

# This bash script does the compiling, linking, and running of x86 asm code.


# Usage
if [[ -z $1 ]]; then
    echo "Usage: bash $0 <asm to be run>"
    exit 1
fi

if [[ $1 = *"asm" ]]; then

    # This is used to compile the code into an elf with the function nasm
    echo "nasm -f elf $1"
    nasm -f elf $1

    # Link the compile x86 binary
    echo "ld -m elf_i386 -s -o $(echo -n $1 | sed 's/[.]asm//g') $(echo -n $1 | sed 's/[.]asm/.o/g')"
    ld -m elf_i386 -s -o $(echo -n $1 | sed 's/[.]asm//g') $(echo -n $1 | sed 's/[.]asm/.o/g')

    echo "------------Result-------------"

    # Run the file
    ./$(echo -n $1 | sed 's/[.]asm//g')
    echo ""

    # This command removes all the compiled and unlinked binaries to with the
    # same name (added it to make things easier to see)
    rm $(echo -n $1 | sed 's/[.]asm/.o/g') && rm $(echo -n $1 | sed 's/[.]asm//g')
else
    echo "ERROR: Not an asm file"
fi
