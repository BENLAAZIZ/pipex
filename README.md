# pipex_git

`Pipex` is a program designed to mimic the behavior of the shell command < file1 cmd1 | cmd2 > file2. It serves as an intermediate level project in C programming that demonstrates proficiency in process management, inter-process communication (IPC) using pipes, and error handling.

## Functionality
The Pipex program takes four arguments:

1. file1 - The name of the input file.
2. cmd1 - The first shell command with its parameters.
3. cmd2 - The second shell command with its parameters.
4. file2 - The name of the output file.

-> The program executes as follows:

* It reads the content of file1.
* Passes the content through cmd1.
* The output of cmd1 is then piped to cmd2.
* The final output of cmd2 is written to file2.
