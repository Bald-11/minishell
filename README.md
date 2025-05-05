# Minishell

A simple shell implementation inspired by bash.

## Authors
- yasserbarhdadi
- ku-uhaku

## Description
Minishell is a simple Unix shell implementation that provides basic command execution, environment variable management, and shell builtins.

## Features
- Command execution
- Input/output redirection
- Pipe handling
- Environment variable management
- Signal handling

## Built-in Commands
- `cd`: Change directory
- `echo`: Display a line of text
- `pwd`: Print working directory
- `export`: Set environment variables
- `unset`: Remove environment variables
- `env`: Display environment variables
- `exit`: Exit the shell

## Usage
```
make
./minishell
```

## Notes
- The shell supports redirection operators (`<`, `>`, `>>`)
- Environment variables can be accessed with `$VAR_NAME`
- Command history is available using up/down arrow keys

## Project Structure
- exec: Command execution and builtin implementation
- utils: Helper functions
- inc: Header files