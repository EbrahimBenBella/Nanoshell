# NanoShell

NanoShell is a lightweight, custom shell implementation in C. It supports built-in commands, variable assignment, and execution of external commands. The shell dynamically manages local variables and allows exporting them to the environment.

## Features
- **Built-in commands**: `echo`, `pwd`, `cd`, `exit`, `export`
- **Local variable storage**: Assign values to variables using `VAR=VALUE`
- **Variable substitution**: Use `$VAR` to substitute stored variables
- **Export variables**: `export VAR` adds a local variable to the environment
- **Execution of external commands**: Runs system commands using `fork` and `exec`

## Compilation
To compile NanoShell, run:
```sh
gcc -o nanoshell nanoshell.c
```

## Usage
Run the shell with:
```sh
./nanoshell
```
### Example Sessions:
```
Nano Shell Prompt > pwd
/home/user

Nano Shell Prompt > x=5
Nano Shell Prompt > echo $x
5

Nano Shell Prompt > folder=home
Nano Shell Prompt > ls /$folder
# Lists contents of /home

Nano Shell Prompt > export x
Nano Shell Prompt > printenv | grep x
x=5

Nano Shell Prompt > exit
Good Bye :)
```

## Implementation Details
- **Command Parsing**: Tokenizes user input and identifies built-in commands or system commands.
- **Variable Handling**: Stores local variables dynamically and supports substitution.
- **Error Handling**: Checks for invalid input formats and system call failures.
- **Process Management**: Uses `fork` and `exec` to execute external commands.

## File Structure
```
📂 NanoShell
├── nanoshell.c    # Main source code
├── README.md      # Documentation

```

## Notes
- Ensure your system has a working `gcc` compiler.
- The shell does **not** support command chaining (e.g., `cmd1 && cmd2`).
- Extra spaces in variable assignment (e.g., `x = 5`) are not allowed.

## Contribution
Feel free to fork and modify NanoShell. Pull requests are welcome!



