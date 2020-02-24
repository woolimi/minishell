# minishell
## How to work together with github
### 1. Clone data from github
```
git clone [remote repository URL]
```
### 2. Create new branch for adding new code
```
git branch [branch_name]
git checkout [branch_name]
// if you want to do at once
git checkout -b [branch_name]
```
### 3. Commit and push to github
```
git add -A
git commit -m [commit_message]
git push -u origin [branch_name]
```
### 4. Ask pull request on github
### 5. Project manager check which code is changed and merge it on github
### 6. Syncronize between remote and local
```
git checkout master
git pull origin master
```
### 7. Start from step 2

## Allowed functions
```
malloc, free, write, open, read, close, fork, wait,
waitpid, wait3, wait4, signal, kill, exit, getcwd,
chdir, stat, lstat, fstat, execve, dup, dup2, pipe,
opendir, readdir, closedir, strerror, errno
```

## Mandatory part
### echo
```
echo -n : do not output the trailing newline
echo normal text
echo $VARIABLE          // env var
echo text1 text2 text3  // multi arg
echo                    // no arg
                        // always exit 0
```

### cd with only a relative or absolute path
```
cd            // go $HOME(no arg)
cd .          // current dir
cd ~          // go $HOME
cd /          // go root
cd not_exist  // exit code 1
```

### pwd (without any options)
```
pwd         // exit code 0
pwd blabla  // exit code 0
```

### export (without any options)
```
export GREET=hello    // exit code 0
export A=1 B=2 C=3    // exit code 0
export A=1 "B =2" C=3 // exit code 1, not a valid identifier
```

### unset (without any options)
```
unset GREET   // exit code 0
unset         // exit code 0
unset A B C   // exit code 0
```

### env (without any options and any arguments)
```
env   // exit code 0
```

### exit (without any options)
```
exit      // exit code 0
exit 1    // exit code 1
exit 1 2  // return 1 Too many arguments
exit abc  // exit code 2 numeric argument required 
```

### ; in the command should separate commands like in bash
```
command1 arg ; command2 arg
command1 arg ; ; // exit code 1, syntax error near unexpected token ';'
```

### ’ and " should work like in bash except for multiline commands
```
echo "$HOME"  // result : /home/wpark
echo '$HOME'  // result : $HOME
```

### Redirections < > “>>” should work like in bash except for file descriptor aggregation
```
command > file : save result into file(create file if not exist)
command >> file : add result into file(create file if not exist)
command < file : give file data to command
command < file_not_exit // No such file or directory, exit code 1
```
for more info [https://putaindecode.io/articles/maitriser-les-redirections-shell/](https://putaindecode.io/articles/maitriser-les-redirections-shell/)

### Pipes | should work like in bash
```
command1 | command2
command1 | | command2 : syntax error near unexpected token `|'
```
for more info [http://www.cs.loyola.edu/~jglenn/702/S2005/Examples/dup2.html](http://www.cs.loyola.edu/~jglenn/702/S2005/Examples/dup2.html)

### Environment variables ($ followed by characters) should work like in bash
```
echo $HOME
```

### $? should work like in bash
```
echo $? // It contains the exit status code of last program. 
```

### ctrl-C, ctrl-D and ctrl-\ should have the same result as in bash
```
ctrl-C : exit programe with interrupt signal.
ctrl-D : EOF
ctrl-\ : generates the QUIT signal. Generally, that signal causes a program to terminate and dump core
```
