# minishell

## Allowed functions
```
malloc, free, write, open, read, close, fork, wait,
waitpid, wait3, wait4, signal, kill, exit, getcwd,
chdir, stat, lstat, fstat, execve, dup, dup2, pipe,
opendir, readdir, closedir, strerror, errno
```

## Mandatory part
* echo
```
echo -n : do not output the trailing newline
echo normal text
echo $VARIABLE
```

* cd (without '-' option)
```
cd [path]
cd .
cd ..
cd /
cd ~
cd [option??????]
```
* pwd (without any options)
* export (without any options)
```
export GREET=hello
```
* unset (without any options)
```
unset GREET
```
* env (without any options and any arguments)
* exit (without any options)
* ; in the command should separate commands like in bash
* ’ and " should work like in bash except for multiline commands
* Redirections < > “>>” should work like in bash except for file descriptor aggregation
```
command > file : save result into file(create file if not exist)
command >> file : add result into file(create file if not exist)
command < file : give file data to command
```
for more info [https://putaindecode.io/articles/maitriser-les-redirections-shell/](https://putaindecode.io/articles/maitriser-les-redirections-shell/)
* Pipes | should work like in bash
* Environment variables ($ followed by characters) should work like in bash
* $? should work like in bash
```
It contains the exit status code of last program.
echo $? 
```
* ctrl-C, ctrl-D and ctrl-\ should have the same result as in bash
```
ctrl-C : exit programe with interrupt signal.
ctrl-D : EOF
ctrl-\ : generates the QUIT signal. Generally, that signal causes a program to terminate and dump core
```
