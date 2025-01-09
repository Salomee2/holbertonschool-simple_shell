# Simple Shell

## Description

This project is a basic shell program. It's designed to mimic a simple version of the standard shell, but without complex features. It handles running commands, but only those without extra options or arguments.

## Attributes

- Interactive Mode: The shell will show a prompt ($), and wait for you to type commands. Once you hit enter, it tries to run the command.
- Non-Interactive Mode: You can also run commands by piping them directly into the shell (using echo or a file).
- Command Search: When you type a command, the shell checks if it's available by looking in the system directories listed in the PATH environment variable.
- Error Messages: If the command cannot be found or if something goes wrong, the shell will show an error message with the name of the command.
- Exit on EOF: If you press `Ctrl+D` (EOF), the shell will exit.

## How to Use

1. Compile the shell with the following command:

    gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o hsh

2. Start the shell by running:

    ./hsh

3. Once inside the shell, type commands like ls or any other available command and press enter to run them.

4. To run a command non-interactively, you can pipe it into the shell. For example:

    echo "/bin/ls" | ./hsh


