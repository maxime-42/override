
# Walkthrough

**Main** : 
The goal is to execute the command "/bin/sh," which essentially opens a shell or command prompt. 
However, to achieve this, we need to provide the correct password.

The program compares two strings: "Q}|usfg~sf{}|a3" and "Congratulations!" using the strcmp function.
If the two strings match, it will execute "/bin/sh."

the first string, "Q}|usfg~sf{}|a3," goes through a process called ROT-18 transformation. 
This means that each character in the string is shifted 18 positions in the ASCII character set. For example, 'Q' becomes 'C,' '}' becomes 'l,' and so on.

**By analyzing these factors**: 
Decrypt Function,  XOR Operation, Comparison, Password Calculation in the test(),  reversing  these help to  deduce that the program employs ROT-18 transformation and that involves finding the correct input (password) 



**Process to exploit :**
>   1. **Input and Decryption**. 
>  2. **Finding the Right Input**


## Step 1

###  Input and Decryption

**Input and Decryption**: You are prompted to enter a password, which is received using `scanf(%u)`. The program then calculates the difference between your input and a predefined value (322424845). If this difference falls within specific limits (1-9 or 16-21), it will use this difference as a parameter for the `decrypt()` function. Otherwise, it uses a random number for decryption.

## Step 2

### Finding the Right Input

To get the correct password and match the two strings, you need to make sure that the decrypt() function executes the ROT-18 operation (to reverse the ROT-18 transformation). To achieve this, you calculate the difference between the expected value (322424845) and 18 (the number of ROT-1 operations needed). So, 322424845 - 18 = 322424827 is the value you should input as your password.

```
level03@OverRide:~$ ./level03 
***********************************
*		level03		**
***********************************
Password:322424827
$ cat /home/users/level04/.pass
kgv3tkEb9h2mLkRsPkXRfc2mHbjMxQzvb2FrgKkf
$ 
