
# Walkthrough

**Main** : 
This program is a simple authentication system that reads a user's login and serial number input and checks whether the input is valid for authentication.
the program checks the length of a login string, looks for tampering with ptrace, and performs a hash-based authentication against a serial number. If all checks pass, the user is granted access to a shell.

**Process to exploit :**
>   1. **Find serial with gdb**



## Step 1

###  Find  serial with gdb

With the  `disas auth` we get the address to breakpoint

**we going to put  2 breakpoints:** 
 1. breakpoint at  `0x080487ba ` to  modify ptrace() return to 0 to pass `set $eax=0`
 2. breakpoint at `0x08048866` while  compared to  print  the hash  which is  it located at `$ebp-0x10` 


```


[Inferior 1 (process 3102) exited with code 01]
(gdb) quit
level06@OverRide:~$ gdb level06 
[...]
(gdb) b *0x080487ba  
Breakpoint 1 at 0x80487ba
(gdb) b *0x08048866 
Breakpoint 2 at 0x8048866
(gdb) r
Starting program: /home/users/level06/level06 
***********************************
*		level06		  *
***********************************
-> Enter Login: mkayumba
***********************************
***** NEW ACCOUNT DETECTED ********
***********************************
-> Enter Serial: 42

Breakpoint 1, 0x080487ba in auth ()
(gdb) set $eax=0
(gdb) c
Continuing.

Breakpoint 2, 0x08048866 in auth ()
(gdb) x/d $ebp-0x10 
0xffffd618:	6234487
(gdb) ^CQuit
(gdb) quit

level06@OverRide:~$ ./level06 
***********************************
*		level06		  *
***********************************
-> Enter Login: mkayumba
***********************************
***** NEW ACCOUNT DETECTED ********
***********************************
-> Enter Serial: 6234487
Authenticated!
$ ls
$ cat /home/users/level07/.pass
GbcPDRgsFK77LNnnuh7QyFYA2942Gp8yKj9KrWD8

```
