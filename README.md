# Simple Shell

**Description:**
A minimalistic shell program that allows users to execute basic command-line operations. This project serves as an educational example and can be a starting point for more advanced shell implementations.

**Table of Contents:**
- [Features](#features)
- [Getting Started](#getting-started)
- [Usage](#usage)
- [Contributing](#contributing)
- [License](#license)

## Features
- Execute basic shell commands.
- Supports simple input/output redirection.

## Getting Started
These instructions will help you set up and run the Simple Shell on your local machine.

### Prerequisites
- A C compiler (e.g., GCC)
- Linux/Unix-based operating system

### Installation
1. Clone the repository:
   ```
   git clone https://github.com/BlackOps99/simple-shell.git
   ```

2. Compile the program:
   ```
   cd simple-shell
   gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o hsh
   ```

## Usage
1. Run the shell:
   ```
   ./simple-shell
   ```

2. You can now execute basic shell commands, such as `ls`, `pwd`, and `echo`.

3. For simple input/output redirection:
   - To redirect input from a file:
     ```
     ./simple-shell < input.txt
     ```

   - To redirect output to a file:
     ```
     ./simple-shell > output.txt
     ```

   - To execute a command and save the output to a file:
     ```
     ./simple-shell -c "ls" > output.txt
     ```

   Replace `ls` with your desired command.


## License
This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

## Authers

