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
* echo
```
echo -n : do not output the trailing newline
echo normal text
echo $VARIABLE
```

* cd with only a relative or absolute path
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
