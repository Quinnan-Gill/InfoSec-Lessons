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

Nothing really happens so lets debug it
