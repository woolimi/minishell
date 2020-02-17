#include "minishell.h"

void	init_env_list(char **env)
{
	char **cut;
	int i;
	t_minish *minish;

	minish = get_minish();
	minish->env = 0;
	i = 0;
	while (env[i])
	{
		cut = ft_split(env[i], '=');
		if (i == 0)
		{
			minish->env = lst_new_env(cut[0], cut[1]);
			minish->env->key = cut[0];
			minish->env->value = cut[1];
		}
		else
			lst_add_env(minish->env, cut[0], cut[1]);
		i++;
	}
}