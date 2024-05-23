#                                  pipex_git

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

<img width="1516" alt="Screen Shot 2024-05-21 at 11 28 01 PM" src="https://github.com/BENLAAZIZ/pipex_git/assets/99501397/5d3c12f9-09f4-4e36-864c-c9dbe81b5a92">


## Detailed Description
### 1. Initialization and Validation:

* Validate the number of arguments.
* Check the accessibility and readability of file1.
* Ensure file2 can be created or written to.

### 2. Process Management:

* Use `fork()` to create child processes for executing cmd1 and cmd2.
* Use `pipe()` to create a pipe for IPC between the processes.
  
### 3. Redirection:

* In the first child process, redirect the standard input (stdin) from file1 and the standard output (stdout) to the write end of the pipe.
* In the second child process, redirect the standard input (stdin) from the read end of the pipe and the standard output (stdout) to file2.

### 4. Execution:

* Execute `cmd1` in the first child process.
* Execute `cmd2` in the second child process.

### 5. Error Handling:

* Handle errors such as invalid commands, file access issues, and pipe creation failures.
* Ensure proper closing of file descriptors and clean up resources to avoid memory leaks.


#
#   Bonus part
#

## Handle multiple pipes.

-> This: 

`$> ./pipex file1 cmd1 cmd2 cmd3 ... cmdn file2`

-> Should behave like:

`< file1 cmd1 | cmd2 | cmd3 ... | cmdn > file2`
## here_doc
* Support « and » when the first parameter is "here_doc".

-> This:

`$> ./pipex here_doc LIMITER cmd cmd1 file`
-> Should behave like:
`cmd << LIMITER | cmd1 >> fil`

<img width="2031" alt="Screen Shot 2024-05-21 at 11 32 42 PM" src="https://github.com/BENLAAZIZ/pipex_git/assets/99501397/ea8184e7-cae5-4b37-b1a4-244457b3f013">


#
