#include "minishell.h"

void		free_env(void)
{
	t_env *env;
	t_env *tmp;

	env = get_minish()->env;		
	while (env)
	{
		tmp = env->next;
		free(env->key);
		free(env->value);
		free(env);
		env = tmp;
	}
}

static void	free_rdir(t_rdir *rdir)
{
	if (rdir)
	{
		free(rdir->file);
		free(rdir);
	}
}

void free_tokens(void)
{
	char **tokens;
	int i;

	tokens = get_minish()->tokens;
	if (tokens)
	{
		i = 0;
		while (tokens[i])
			free(tokens[i++]);
		free(tokens);
		get_minish()->tokens = 0;
	}
}

void free_line(void)
{
	char *line;

	line = get_minish()->line;
	if (line)
		free(line);
	get_minish()->line = 0;
}

void		free_cmd()
{
	t_cmd	*cmd;
	t_cmd	*tmp;
	int		i;

	free_line();
	free_tokens();
	cmd = get_minish()->cmd;
	while (cmd)
	{
		tmp = cmd->next;
		if (cmd->argv)
		{
			i = -1;
			while (cmd->argv[++i])
				free(cmd->argv[i]);
			free(cmd->argv);
		}
		free_rdir(cmd->in);
		free_rdir(cmd->out);
		free_rdir(cmd->out_dbl);
		free(cmd);
		cmd = tmp;
	}
	get_minish()->cmd = 0;
}

void		free_all()
{
	free_cmd();
	free_env();
}
