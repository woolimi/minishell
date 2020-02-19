#include "minishell.h"

void	free_env()
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

void	free_rdir(t_rdir *rdir)
{
	if (rdir)
	{
		free(rdir->file);
		free(rdir);
	}
}

void	free_cmd()
{
	t_cmd	*cmd;
	t_cmd	*tmp;
	int		i;

	cmd = get_minish()->cmd;
	while (cmd)
	{
		tmp = cmd->next;
		if (cmd->argv)
		{
			i = -1;
			while (cmd->argv[++i])
				free(cmd->argv[i]
			free(cmd->argv);
		}
		free_rdir(rdir->in);
		free_rdir(t_rdir->out);
		free_rdir(t_rdir->out_dbl);
		cmd = tmp;
	}
}

void	free_all()
{

}
