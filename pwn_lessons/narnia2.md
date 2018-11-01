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

So this one requires overflowing the return address, so how do we do that. Well we just do guess and check. Try:

`$ ./narnia2 $(python -c  'print "A" * <value')`

with `<value>` greater than 128, and try to get a seg fault.


Then bust open gdb and try it again, but this time it will say what it is having trouble returning to. Try to get it so that there is a 0x0041 near end. Then what ever  that value is try that is the max size of the buffer. Use the `x/<number>x $esp` command to see the end of the  buffer (this is the top of the stack) and where it is in memory. Then construct the payload

Using that max value, the shellcode from narnia1, and the address of top of stack.
```
+---------------------+--------------+-------------------+
|                     |              |                   |
|   buffer overflow   |   shellcode  |  return address   |
|                     |              |                   |
+---------------------+--------------+-------------------+
```

Now execute with  python command line.
