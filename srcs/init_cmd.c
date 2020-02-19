#include "minishell.h"

/*
** tokens = { "cat", "Makefile", ">", "file.txt", "|", ...}
** 
** typedef struct	s_cmd
** {
** 	char	**argv; // { "cat", "Makefile" , NULL}
** 	int		is_pipe;	// 1
** 	int		is_rdir;	// 1
** 	t_rdir	*in;
** 	t_rdir	*out;	// file = file.txt, fd = open()
** 	t_rdir	*out_dbl;
** 	struct s_cmd *next;
** }				t_cmd;
** 
*/

static void	lst_add_ispipe_cmd(t_cmd *cmd)
{
	t_cmd *last;

	last = lst_last_cmd(cmd);
	last->is_pipe = 1;
}

static void	lst_add_redir_cmd(t_cmd *cmd, char *redir, char *file)
{
	t_cmd *last;

	last = lst_last_cmd(cmd);
	last->is_rdir = 1;
	if (ft_strequ(redir, "<"))
	{
		last->in = malloc(sizeof(t_rdir));
		last->in->fd = -1;
		last->in->file = ft_strdup(file);
	}
	else if (ft_strequ(redir, ">"))
	{
		last->out = malloc(sizeof(t_rdir));
		last->out->fd = -1;
		last->out->file = ft_strdup(file);
	}
	else if (ft_strequ(redir, ">>"))
	{
		last->out_dbl = malloc(sizeof(t_rdir));
		last->out_dbl->fd = -1;
		last->out_dbl->file = ft_strdup(file);
	}
}

static int		count_arr(char **arr)
{
	int i;

	i = 0;
	while (arr[i])
		i++;
	return (i);
}

static int get_key(char key[], char *arg)
{
	int i;

	i = 0;
	while (arg[i] && arg[i] != ' ' && arg[i] != '$')
	{
		key[i] = arg[i];
		i++;
	}
	key[i] = '\0';
	return (i);
}

static char *change_env_to_value(char *arg)
{
	char buff[1024];
	char key[100];
	char *value;
	int i;

	ft_memset(buff, 0, 1024);
	i = 0;
	while (*arg)
	{
		if (*arg == '$' && *(arg + 1) == '?')
		{
			i = ft_strlcat(buff, ft_itoa(get_minish()->excode), sizeof(buff));
			arg += 2;
		}
		else if (*arg != '$' ||
			(*arg == '$' && (!*(arg + 1) || *(arg + 1) == ' ')))
			buff[i] = *arg++;
		else
		{
			arg += get_key(key, ++arg);
			value = lst_find_env(key);
			i = ft_strlcat(buff, value, sizeof(buff));
		}
		i++;
	}
	buff[i] = '\0';
	return ft_strdup(buff);
}

static void	lst_add_argv_cmd(t_cmd *cmd, char *arg)
{
	t_cmd	*last;
	int		cnt;
	char	**new_arr;
	int		i;

	last = lst_last_cmd(cmd);
	cnt = count_arr(last->argv);
	new_arr = malloc(sizeof(char*) * (cnt + 2));
	i = 0;
	while (i < cnt)
	{
		new_arr[i] = last->argv[i];
		i++;
	}
	new_arr[i] = change_env_to_value(arg);
	new_arr[cnt + 1] = NULL;
	free(last->argv);
	last->argv = new_arr;
}

int	init_cmd_list(char **tokens)
{
	t_minish *minish;
	int i;
	int fnew;

	if (!ck_tokens(tokens))
		return (0);
	minish = get_minish();
	minish->cmd = 0;
	i = 0;
	fnew = 1;
	while (tokens[i])
	{
		if (fnew && !(fnew = 0))
			minish->cmd = lst_add_cmd(minish->cmd, tokens[i]);
		else if (ft_strequ(tokens[i], "|") && (fnew = 1))
			lst_add_ispipe_cmd(minish->cmd);
		else if (is_redir(tokens[i]) && (i++))
			lst_add_redir_cmd(minish->cmd, tokens[i - 1], tokens[i]);
		else if (ft_strequ(tokens[i], ";") && (fnew = 1))
		{
			i++;
			continue;
		}
		else
			lst_add_argv_cmd(minish->cmd, tokens[i]);
		i++;
	}
	return (1);
}