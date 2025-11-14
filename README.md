# mycp

A minimal reimplementation of the UNIX cp command written in C.
This project demonstrates low-level file handling using POSIX system calls (open, read, write, close).

### Overview

mycp copies the contents of one file to another using a fixed-size buffer.
It validates arguments, reports errors through stderr, and returns non-zero exit codes when failures occur.
The destination file is created if needed and truncated if it already exists.

### Usage
- Compile:
`gcc -Wall -Wextra -o mycp mycp.c`
- Run:
`./mycp SOURCE DEST`
- Example:
`./mycp input.txt copy.txt`

### Features
- Buffered copying using POSIX system calls
- Automatic file creation (mode 0644)
- Truncation of existing destination files
- Clear error messages based on errno

### Limitations

- Does not support directories
- No recursive copying
- No flags or metadata preservation
- Handles exactly one source and one destination file

### Purpose
I built this project to gain a clearer understanding of POSIX system calls and their role in low-level file operations. Through this implementation, I learned how system calls behave, how they interact with the operating system, and how to handle errors reliably and correctly
