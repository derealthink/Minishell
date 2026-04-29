# Minishell

Minishell is a 42 school project that recreates a simplified Unix shell in C.  
It supports command parsing, pipes, redirections, environment variable expansion, and common built-in commands.

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
- Input/output redirections and heredoc handling.

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

## Notes

This project focuses on process management, file descriptors, signal handling, and shell behavior.  
Its behavior is designed to stay close to bash where required by the project rules.

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

## Authors
- [jqrsound](https://github.com/jqrsound)
- [derealthink](https://github.com/derealthink)
