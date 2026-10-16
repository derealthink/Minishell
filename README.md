> **Moved:** the maintained public copy is now in [42-school/projects/Minishell](https://github.com/derealthink/42-school/tree/main/projects/Minishell). This repository is retained as a historical archive.

# Minishell

<p align="center">
  <img src="https://img.shields.io/badge/Language-00599C?logo=c&logoColor=white" alt="C Badge" />
  <img src="https://img.shields.io/badge/Shell-Bash?logo=gnu-bash&logoColor=white" alt="Shell Badge" />
  <img src="https://img.shields.io/badge/42%20School-Project-000000" alt="42 Badge" />
</p>

<p align="center">
  <strong>Minishell</strong> is a 42 school project that recreates a simplified Unix shell in C.
</p>

## Overview

Minishell is a command-line shell written in **C** that mimics key Bash-like behavior.  
It handles parsing, execution, redirections, pipes, environment variables, and built-in commands.

## Features

- Prompt display and command history.
- Parsing of commands, quotes, pipes, and redirections.
- Environment variable expansion, including `$?`.
- Built-in commands:
  - `echo`
  - `cd`
  - `pwd`
  - `export`
  - `unset`
  - `env`
  - `exit`
- Execution of external commands using the system `PATH`.
- Input/output redirections.
- Heredoc support.
- Signal handling for interactive shell behavior.

**Key learning objectives:**
- Lexical analysis and parsing
- Process creation and `execve`
- File descriptor manipulation
- Signal handling (`SIGINT`, `SIGQUIT`)
- Memory management without leaks

## Build

```bash
make
```

## Run

```bash
./minishell
```
## Example

```bash
$ ./minishell
minishell$ echo "Hello World"
Hello World
minishell$ echo $?
0
minishell$ ls -la | grep Makefile | wc -l
1
minishell$ cat << EOF > test.txt
> line1
> line2
> EOF
minishell$ cat test.txt
line1
line2
minishell$ exit
```

## Signals

- `Ctrl+C` (`SIGINT`) → sends SIGINT to active process
- `Ctrl+D` → exit shell


## Notes

This project focuses on process management, file descriptors, signal handling, and shell behavior.  
Its behavior is designed to stay close to bash where required by the project rules.


## Authors
- [jqrsound](https://github.com/jqrsound)
- [derealthink](https://github.com/derealthink)

---

Part of my [42 School project collection](https://github.com/derealthink/42-school).
