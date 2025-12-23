# Minishell

A simple shell implementation inspired by Bash, recreating essential shell functionality from scratch.

## About

This project recreates a basic Unix shell with essential features including command execution, pipes, redirections, and environment variable handling. This is a team project from the 42 School curriculum that serves as an introduction to process management, system programming, and Unix system calls.

## Features

### Core Functionality
- Interactive command prompt with working history
- Executable search using PATH variable
- Support for relative and absolute paths
- Quote handling (single `'` and double `"`)
- Environment variable expansion (`$VAR`, `$?`)
- Signal handling (ctrl-C, ctrl-D, ctrl-\)

### Redirections
- `<` - Input redirection
- `>` - Output redirection
- `<<` - Here document (delimiter-based input)
- `>>` - Output redirection in append mode

### Advanced Features
- Pipes (`|`) - Connect command outputs to inputs
- `$?` - Exit status of last command
- Proper signal handling in interactive mode

### Built-in Commands
- `echo` with `-n` option
- `cd` with relative or absolute path
- `pwd` - Print working directory
- `export` - Set environment variables
- `unset` - Remove environment variables
- `env` - Display environment
- `exit` - Exit the shell

## Signal Handling

### Interactive Mode

| Signal | Key Combination | Behavior |
|--------|----------------|----------|
| SIGINT | `ctrl-C` | Display new prompt on new line |
| EOF | `ctrl-D` | Exit the shell |
| SIGQUIT | `ctrl-\` | Do nothing (ignored) |

## Quote Handling

### Single Quotes (`'`)
Prevent interpretation of all metacharacters:
```bash
minishell$ echo '$USER is $HOME'
$USER is $HOME
```

### Double Quotes (`"`)
Prevent interpretation of metacharacters except `$`:
```bash
minishell$ echo "$USER is at $HOME"
username is at /home/username
```

## Requirements

- C compiler (gcc/clang)

## Installation

```bash
git clone https://github.com/marinezh/42school_Minishell.git
cd minishell
make
```

## Usage

```bash
./minishell
```

Then use it like a regular shell:
```bash
minishell$ echo "Hello World"
minishell$ ls -la | grep minishell
minishell$ cat < input.txt > output.txt
minishell$ exit
```

## Technical Implementation

### Key Concepts

**Process Management:**
- `fork()` - Create child processes
- `execve()` - Execute commands
- `wait()` - Wait for child processes

**Pipes:**
- `pipe()` - Create pipe file descriptors
- `dup2()` - Duplicate file descriptors

**Signals:**
- `signal()` - Set up signal handlers
- Global variable for signal indication

**File Descriptors:**
- Input/output redirection using `open()`, `close()`, `dup2()`

---

*42 School Project - 2025*