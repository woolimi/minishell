#include "minishell.h"

void	exec_env(t_cmd *cmd)
{
	t_env *env;

	if (cmd->is_rdir)
	{
		// dup, dup2
	}
	env = get_minish()->env;
	while (env)
	{
		ft_putstr(env->key);
		ft_putstr("=");
		ft_putstr(env->value);
		ft_putstr("\n");
		env = env->next;
	}
	// backup dup, dup2
}