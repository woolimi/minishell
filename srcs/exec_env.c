#include "minishell.h"

static void print_env(t_env *env)
{
	while (env)
	{
		ft_putstr(env->key);
		ft_putstr("=");
		ft_putstr(env->value);
		ft_putstr("\n");
		env = env->next;
	}
}

int	exec_env(t_cmd *cmd)
{
	t_env *env;

	if (cmd->argv[1])
	{
		/* need to add */
	}
	print_env(get_minish()->env);
	return (EXIT_SUCCESS);
}