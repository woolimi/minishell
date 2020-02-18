#ifndef WOOLIM_H
# define WOOLIM_H

typedef struct s_env
{
	char *key;
	char *value;
	struct s_env *next;
} t_env;

typedef struct	s_rdir
{
	char	*file;
	int		fd;
	int	save_fd;
}				t_rdir;

// tokens = { "cat", "Makefile", ">", "file.txt", "|", ...}
typedef struct	s_cmd
{ 
	char	**argv; // { "cat", "Makefile" , NULL}
	int		is_pipe;	// 1
	int		is_rdir;	// 1
	t_rdir	*in;
	t_rdir	*out;	// file = file.txt, fd = open()
	t_rdir	*out_dbl;
	struct s_cmd *next;
}				t_cmd;

typedef struct s_minish
{
	char	*line;
	t_env	*env;
	t_cmd	*cmd;
	int		executed;
} t_minish;

t_minish *get_minish(void);
void exec_env(t_cmd *cmd);
void exec_unset(t_cmd *cmd);
void exec_export(t_cmd *cmd);

void init_env_list(char **env);
void lst_remove_env(char *key);
t_env *lst_add_env(t_env *begin, char *key, char *value);
t_env *lst_new_env(char *key, char *value);
void lst_check_and_add_env(char *key, char *value);
int is_redir(char *s);

int ck_tokens(char **tokens);
int	init_cmd_list(char **tokens);

t_cmd *lst_new_cmd(char *token);
t_cmd *lst_add_cmd(t_cmd *begin, char *token);
t_cmd *lst_last_cmd(t_cmd *cmd);
int syntax_error(char *token, int ret);
void	exec_command(void);
char **get_built_in(void);
int no_exec_error(char *cmd, int ret);
void exec_non_built_in(t_cmd *cmd);
void exec_exit(t_cmd *cmd);
int no_file_error(char *file, int ret);
void redirection(t_cmd *cmd);
void close_redirection(t_cmd *cmd);
t_cmd *piping(t_cmd *cmd);
int is_built_in(char *arg);
void exec_built_in(int btin_nb, t_cmd *cmd);
void exec_pwd(t_cmd *cmd);
int too_many_arg_error(char *cmd, int ret);
void	exec_cd(t_cmd *cmd);
void	exec_echo(t_cmd *cmd);
#endif
