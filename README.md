# minishell

A minimal Unix shell implementation written in C, recreating the basic functionality of bash/zsh.

## 📋 Table of Contents

- [Overview](#overview)
- [Features](#features)
- [Build Instructions](#build-instructions)
- [Usage](#usage)
- [Built-in Commands](#built-in-commands)
- [Supported Features](#supported-features)
- [Project Structure](#project-structure)
- [Development Workflow](#development-workflow)

## Overview

Minishell is a simplified shell implementation that provides core shell functionality including command execution, piping, redirection, environment variable management, and signal handling. It serves as an educational project to understand how shells work at a low level.

## Features

- ✅ **Command Execution**: Execute both built-in and external commands
- ✅ **Piping**: Chain commands using pipes (`|`)
- ✅ **Redirection**: Input (`<`) and output (`>`, `>>`) redirection
- ✅ **Environment Variables**: Manage and expand environment variables (`$VAR`)
- ✅ **Quote Handling**: Support for single quotes, double quotes, and escape sequences
- ✅ **Signal Handling**: Proper handling of `SIGINT` (Ctrl+C) and `SIGQUIT` (Ctrl+\)
- ✅ **Command Separation**: Support for semicolon (`;`) to separate commands
- ✅ **Error Handling**: Comprehensive error messages and exit codes

## Build Instructions

### Prerequisites

- GCC compiler
- Make
- Unix-like operating system (macOS, Linux)

### Compilation

```bash
# Clone the repository
git clone [remote repository URL]

# Navigate to the project directory
cd minishell

# Build the project
make

# Run minishell
./minishell
```

### Makefile Targets

- `make` or `make all`: Compiles the project
- `make clean`: Removes object files
- `make fclean`: Removes object files and executable
- `make re`: Rebuilds the project from scratch

## Usage

Once compiled, run `./minishell` to start the shell. You'll see a prompt:

```
MINISHELL$
```

You can now enter commands just like in a regular shell:

```bash
MINISHELL$ ls -la
MINISHELL$ echo "Hello, World!"
MINISHELL$ pwd
MINISHELL$ cd /path/to/directory
MINISHELL$ exit
```

## Built-in Commands

The following commands are implemented as built-ins (executed directly by the shell):

| Command  | Description                   | Example             |
| -------- | ----------------------------- | ------------------- |
| `echo`   | Print arguments to stdout     | `echo hello world`  |
| `cd`     | Change directory              | `cd /home/user`     |
| `pwd`    | Print working directory       | `pwd`               |
| `export` | Set environment variable      | `export VAR=value`  |
| `unset`  | Unset environment variable    | `unset VAR`         |
| `env`    | Display environment variables | `env`               |
| `exit`   | Exit the shell                | `exit` or `exit 42` |

## Supported Features

### Piping

Chain multiple commands together:

```bash
MINISHELL$ ls | grep .c
MINISHELL$ cat file.txt | wc -l
MINISHELL$ echo "hello" | cat
```

### Redirection

**Input Redirection (`<`):**

```bash
MINISHELL$ cat < file.txt
```

**Output Redirection (`>` and `>>`):**

```bash
MINISHELL$ echo "hello" > output.txt
MINISHELL$ echo "world" >> output.txt
```

### Environment Variables

Expand environment variables using `$VAR`:

```bash
MINISHELL$ echo $HOME
MINISHELL$ export MY_VAR=test
MINISHELL$ echo $MY_VAR
```

### Quote Handling

- **Single quotes**: Preserve literal content
- **Double quotes**: Allow variable expansion
- **Escape sequences**: Use backslash (`\`) to escape special characters

### Command Separation

Execute multiple commands on one line:

```bash
MINISHELL$ ls; pwd; echo done
```

### Signal Handling

- **Ctrl+C** (`SIGINT`): Interrupts the current command or returns to prompt
- \*\*Ctrl+\*\* (`SIGQUIT`): Quits the current command (if running)

## Project Structure

```
minishell/
├── includes/
│   ├── minishell.h      # Main header file with function declarations
│   └── struct.h         # Data structure definitions
├── srcs/
│   ├── main.c           # Entry point and main loop
│   ├── lexer_1.c        # Tokenization (lexing)
│   ├── lexer_2.c        # Lexer helper functions
│   ├── parser_1.c       # Command parsing
│   ├── init_cmd.c       # Command list initialization
│   ├── exec_command.c   # Command execution logic
│   ├── exec_*.c         # Built-in command implementations
│   ├── pipe.c           # Pipe implementation
│   ├── redirection.c    # I/O redirection
│   ├── dollar_quotes.c  # Variable expansion and quote handling
│   ├── lst_*.c          # Linked list operations
│   ├── free_*.c         # Memory management
│   └── error_*.c        # Error handling
├── lib/
│   └── libft/           # Custom C library (string, memory functions)
├── Makefile             # Build configuration
└── README.md            # This file
```

### Key Data Structures

- **`t_minish`**: Main shell state (commands, environment, tokens)
- **`t_cmd`**: Command structure (arguments, pipes, redirections)
- **`t_env`**: Environment variable linked list
- **`t_rdir`**: Redirection information (file, file descriptor, type)

## Development Workflow

### 1. Clone the Repository

```bash
git clone [remote repository URL]
```

### 2. Create a New Branch

```bash
# Create and switch to a new branch
git checkout -b [branch_name]

# Or do it in two steps
git branch [branch_name]
git checkout [branch_name]
```

### 3. Make Changes and Commit

```bash
# Stage all changes
git add -A

# Commit with a descriptive message
git commit -m "[commit_message]"

# Push to remote repository
git push -u origin [branch_name]
```

### 4. Create a Pull Request

Create a pull request on GitHub for code review.

### 5. Sync with Main Branch

After your changes are merged:

```bash
git checkout master
git pull origin master
```

## Resources

### Redirections and Pipes

1. [Mastering Shell Redirections](https://putaindecode.io/articles/maitriser-les-redirections-shell/)
2. [dup2() Examples](http://www.cs.loyola.edu/~jglenn/702/S2005/Examples/dup2.html)

## Technical Details

- **Language**: C
- **Standard**: C99
- **Compilation Flags**: `-Wall -Wextra -Werror`
- **Memory Management**: Manual allocation/deallocation
- **Process Management**: `fork()`, `execve()`, `wait()`, `waitpid()`
- **File Descriptors**: `dup()`, `dup2()`, `pipe()`, `open()`, `close()`
- **Signals**: `signal()`, `SIGINT`, `SIGQUIT`

## Notes

- This is an educational project and may not handle all edge cases that production shells handle
- Some advanced shell features (like job control, history, tab completion) are not implemented
- The shell uses a custom `libft` library for string and memory operations

---

**Authors**: wpark, froussel  
**Project**: 42 School minishell project
