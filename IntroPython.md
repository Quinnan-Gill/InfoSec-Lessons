# Intro to Python

## What is Python?

Python is a very easy to use scripting language. It is used in everything form web based backend (like Flask and Django) to data science (with libraries such as numpy and pandas). It is incredibly useful in hacking. Today we will be going over the basics of the python language and try to make a zip password cracker.

## Install Python

#### Windows
Go to [anaconda](https://www.anaconda.com/download) to install python (2.7 is preferred). Then:
1. Open System Properties
2. Click `Advanced system settings` in the sidebar.
3. Click `Environment Variables...`
4. Select `PATH` in the `System variables` section
5. Click `Edit`
6. Add Python's path to the end of the list
7. Open command prompt and type `python`
8. If 7 does not work type in command prompt `echo $PATH` and call over an instructor

9. Try in command prompt typing `ipython`
10. If 9 does not work try `conda install -c anaconda ipython` and try again.

To create python scripts you can use a text editor i perfer [atom](https://atom.io/)

### Mac
Can go [anaconda](https://www.anaconda.com/download) route but I suggest going the [home brew way](https://brew.sh/).

Then `python -m pip install --upgrade setuptools`

Then `pip install ipython`

### Linux
`sudo apt-get install python`

Then stack overflow from there ¯\\\_(ツ)\_/¯

## Starting Basic Python

#### Hello, World!

In terminal/command prompt type ($ means terminal):

```python
$ python
In [1]: print "Hello, World"
Hello, World
```

Yea, you just typed your first python code. Congrats.

#### Variables
Python uses [duck](https://www.google.com/imgres?imgurl=https%3A%2F%2Fkids.nationalgeographic.com%2Fcontent%2Fdam%2Fkids%2Fphotos%2Fanimals%2FBirds%2FH-P%2Fmallard-male-swimming.ngsversion.1396907279296.adapt.1900.1.jpg&imgrefurl=https%3A%2F%2Fkids.nationalgeographic.com%2Fanimals%2Fmallard-duck%2F&docid=i1eKbLqxaanTIM&tbnid=9Ipo6LhhU012TM%3A&vet=10ahUKEwjDnrvqve3dAhVjh-AKHSnPAFIQMwh4KAEwAQ..i&w=1900&h=1068&bih=872&biw=1496&q=duck&ved=0ahUKEwjDnrvqve3dAhVjh-AKHSnPAFIQMwh4KAEwAQ&iact=mrc&uact=8) typing so you don't have to declare what the variable is.

```python
In [2]: num = 21

In [3]: words = 'Strings are in quotes'

In [4]: num
Out[4]: 21

In [5]: words
Out[5]: "Strings are in quotes"

In [6]: type(num)
Out[6]: int

In [7]: type(words)
Out[7]: str
```

Can't put to variables of different types together or else you get an error.
```python
In [8]: print num + words

TypeError
```

#### Strings
Strings are just a bunch of characters put together (like words). They can be in single quotes`'Hello'` or double quotes `"Hello"`

Strings can be manipulated and and changed and changed with functions.
```python
In [9]: print words.upper()
STRINGS ARE IN QUOTES

In [11]: print words.lower()
strings are in quotes

In [12]: print words.replace('in quotes', "the coolest")
Strings are the coolest

In [14]: print words[7:15] # get the characters in index 4-13
are in

In [15]: print words[4:-2] # get the characters in index from 4 to -2 (2 from end)
ngs are in qu

In [16]: print words[4::] # 4 to end of string
ngs are in quotes

In [17]: print words[4:-2:2] # 4 to -2 every second char
nsaei ut

In [18]: len(words) # get number of characters
Out[18]: 21

In [19]: words.split(' ') # split on space
Out[19]:['Strings', 'are', 'in', 'quotes']
```

What are those weird brackets doing? We will get to that next!

###### Some Practice
Use stackoverflow to help.

For the string `"Would you like to eat breakfast"`
1. Turn the first half of it all lower case (use the indexing)
2. Turn the last half of it all upper case
3. Turn replace the word `'breakfast'` with `'pumpkin pie'`
4. Add the entire alphabet to end of string (use + operator to append strings)

#### Lists
Lists are exactly like they sound. They are ordered items, called arrays in other languages.

```python
In [20]: lst = []

In [21]: lst.append(13) # add values to end of list

In [22]: lst.append("word") # can be different data types in a list

In [23]: lst.append(64)

In [24]: lst.append(99)

In [25]: print lst
[13, 'word', 64, 99]

In [26]: lst[2] = 'dogs' # 3rd element because lists start at 0

In [27]: print lst
[13, 'word', 'dogs', 99]

In [28]: lst.index(13) # where is 13?
Out[28]: 0

In [29]: lst.remove('word')

In [30]: lst
Out[30]: [13, 'dogs', 99]
```

###### Some Practice
Reverse the list `[9,8,7,6,5,4,3,2,1]`

#### If, else and elif

So when it comes to control structure you may want to branch you code. So to do this you use if-else.

```python
if [condition]:
    # runs if condition is true
else:
    # runs if the condition is false
```
```python
In [31]: if 1 == 1:
    ...:    print "It is true"
    ...: else:
    ...:    print "The condition is false"
It is true

In [32]: if 1 != 1:
    ...:    print "It is True"
    ...: else:
    ...:    print "The condition is false"
The condition  is false
```
Use an elif to increase complexity in structure.
```python
In [33]: if 1 == 2:
    ...:    print "It is True"
    ...: elif 2 == 2:
    ...:    print "The elif is true"
    ...: else:
    ...:    print "The condition is False"
The elif is true
```

###### Some Practice
Have it so a control flow that will print out the complement of a given variable (complement of 1 is 9, 2 is 8,...)

#### Exception Handeling
If you want to run your code with a sketchy operation that may cause an error, you use try except to help handle the error and continue running on smoothly.
```python
try:
    # some dangerous code
except:
    # do this if it went wrong
```
```python
In [34]: try:
    ...:    print "[+] 1337/0 = " + str(1337/0)  # need str() to print int values
    ...: except:
    ...:    print "[-] Error"
```

#### Functions
This helps encapsulate code and makes writing everything easier.
```python
def funct_name(args):
    # do stuff
    return val
```
```python
In [35]: def square(x):
    ...:    return x ** 2

In [36]: y = 4

In [36]: print "The square of y is " + str(funct_name(y))
The square of y is 16
```

#### For loops
To iterate over something you use a for loop
```python
In [37]: for x in range(1, 10):
    ...:    print x
1
2
3
4
5
6
7
8
9
```
Can also do it to items in lists and strings
```python
In [38]: lst = [1, 'dogs', 13]

In [39]: for l in lst:
    ...:    print l
1
'dogs'
13

In [40]: cat_str = "cat"

In [41]: for char in cat_str:
    ...:    print char
c
a
t
```
### Great you are done with the basics
There is obviously way more python to explore and experiment with and will be an incredible tool used pretty much every where in the modern age. Have fun.

## Starting Violent Python
We are going to create a zip cracker that will brute force a zip file that is password protected by running a dictionary attack. A dictionary attack is basically running through every word in a text file and trying that as the password.

Get the `dictionary.txt` and the `evil.zip` from slack.
Try in ipython:
```python
In [1]: import zipfile
```
If it gives you an error pip install it (may need help from instructor)

### Skeleton Code
It you try opening the zip file it will ask you for a password. We want no password.

The zipfile import is just a library to handle zipfiles (duh). So lets start.
```python
import zipfile
zFile = zipfile.ZipFile("evil.zip")

zFile.extractall(pwd="oranges")
```
Save this as zipCracker.py and go to command prompt and type:

> $python zipCracker.py

It should raise a python error (if there is a system error get instructor). What should we do to make sure it does not crash?



Use a try except to catch the error and run a different part of the program.
```python
import zipfile
zFile = zipfile.ZipFile("evil.zip")
try:
    zFile.extractall(pwd="oranges")
except Exception, e:
    print e
```

No running it returns:
```
$ python unzip.py
('Bad password for file', <zipfile.ZipInfo object at 0xXXXXXXXX)
```

Now lets try using the different passwords from `dictionary.txt`.
This requires an input/output operation (I/O) to open the dictionary and read the values.

To use open a plaintext file like a `txt` use open.
```python
import zipfile
zFile = zipfile.ZipFile("evil.zip")
passFile = open('dictionary.txt') # open the file
for line in passFile.readlines(): # read each line
    passFile = line.strip('\n') # what is the \n
    try:
        zFile.extractall(pwd=password)
        print "[+] Password = " + password + "\n" # there it is again
        exit(0)
    except Exception, e:
        print e
```
This code takes in each line of `dictionary.txt` and tries it as a password. `\n` is an escape character meaning new line. We want to remove it from the end (or strip it) from the line so we just get the readable characters.

Now lets encapsulate this.
```python
import zipfile
def extractFile(zFile, password):
    try:
        zFile.extractall(pwd=password)
        return password
    except:
        return # Return none

def main():
    zFile = zipfile.ZipFile("evil.zip")
    passFile = open('dictionary.txt') # open the file
    for line in passFile.readlines(): # read each line
        passFile = line.strip('\n') # what is the \n
        guess = extractFile(zFile, password)
        if guess:
            print '[+] Password = ' + password + '\n'
            exit(0)
if __name__ == '__main__':
    main()
```
The weird looking if statement is the syntax magic for the actual start of the function.
Then start calls main() which extracts the zip file and runs the dictionary attack.

This will work, however this is very slow and may take forever if we have a huge dictionary. So lets speed it up with threads

#### Adding Threads
Threads are a way for concurrency in python. What happens is the process forks into multiple different subprocesses until. A solution is found.
```python
import zipfile
from threading import Thread
def extractFile(zFile, password):
    try:
        zFile.extractall(pwd=password)
        print '[+] Password = ' + password + '\n'
    except:
        pass # do nothing if there is an error and just continue on

def main():
    zFile = zipfile.ZipFile("evil.zip")
    passFile = open('dictionary.txt') # open the file
    for line in passFile.readlines(): # read each line
        passFile = line.strip('\n') # what is the \n
        t = Thread(target=extractFile, args=(zFile, password))
        t.start()
if __name__ == '__main__':
    main()
```
This will concurrently run the extract file function all at the same time. Then the one found is printed to the console.
