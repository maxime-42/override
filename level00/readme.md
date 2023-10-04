
# Walkthrough

**Main** : 
The line `system("/bin/sh")` in the source code is used to execute a shell with authenticated access if the correct password is entered. <br/>
This program  essentially opens a new shell, providing a command prompt to the user<br/>


**To run this code successfully, follow these steps:**
>   1. Run the executable
>   2. Give a parameter

## Step 1

###  Run the executable

`./level00`

## Step 2 
### Get the correct parameter 
when we analyse the program we can saw that  the programme check if the entered password is correct  `5276` 
if it's correct  the  `system("/bin/sh")` will be executed 

```
if (password != 0x149c) { 
	printf("\nInvalid Password!\n"); 
	return  false; 
} 
else { 
	printf("\nAuthenticated!\n"); 
	// Execute a shell with authenticated access 
	system("/bin/sh"); 
	return  true; 
}
```
When the program prompts  for a password, enter the correct password, which is `0x149c` in hexadecimal and   `5276` in decimal.
```
Password: 5276`
$ cat /home/users/level01/.pass
uSq2ehEGT6c9S24zbshexZQBXUGrncxn5sD5QfGL

```
