# Introduction to Bash Scripting

So say there are 10,000 files in a directory and you want to move all the files that have a .html, .js, or .css. To a directory called front_end/. And from there you want to move all the .js files into a components/ directory and the .css into the css/ directory for your front end application.

If you have experience with Python's os or subprocess library, or Java's ProcessBuilder, or C's execv (or other) commands you could do this in that language. Bash is basic a way not to need special commands or libraries. It is practically a way to run linux commands one after eachother and perform control flow. Bash is uses just linux commands like ls, find, mkdir, etc.

### Announcements
* https://teaser.insomnihack.ch/

### Schedule
* Announcements
* Introduction to Bash scripting
* Hackover bash challenge review
* OverTheWire Level 22 and up

### Cheat Sheet

Bash scripting for me has been a lot of google foo.
https://devhints.io/bash


## Control Flow
So you are currently you are in the directory with all the files. First create the directory called FrontEnd/. But you do not know if it exists are not so how need CONTROl FLOW. We need an if statement:
``` bash
if [ {LOGIC} ]; then
    {statements}
fi
```
So check in the if statement's logic to see if the directory does not exist. Using `NOT --directory [directory name]`
``` bash
if [ ! -d ./front_end ]; then
    mkdir -p ./front_end # the -p makes any needed directories not listed
fi
```

## Loops and Regex
Now you need to move all the files that have .js, .html, or .css. You could do this that with wildcards. But say there is are .java files (files that are not the wanted files) so we need regex on an ls command. Regex stands for regular expression, and it is a way to search in strings with our needing. We use grep to get all the files. Grep stands for Global regular expression print. We use the grep command:
``` bash
grep -r -i --include \*.html --include \*.css --include \*.js
```

So to harness that output put `$()`

So we want to take each line of the output and put it into a for loop to do for loop it is kind of like pythons or Java's for each loop.
``` bash
for [unit] in $(items)
do
    # statements
done
```
So for each file in the output of the grep expression and do logic on it
``` bash
for file in $(grep -r -i --include \*.html --include \*.css --include \*.js)
do
    mv $file ./front_end
done
```

So here are some of the basics to bash scripting. It gets more complicated with functions and different linux commands but it is super useful.

## CTF challenge

Use thoth or pitt ssh and go to directory `/afs/pitt.edu/home/q/c/qcg1/ctf/`

## OverTheWire

Level 22 is where we get into bash scripting the ssh is:
`ssh bandit20@bandit.labs.overthewire.org -p 2220`
Password: Yk7owGAcWjwMVRwrTesJEwB7WVOiILLI
