#include "minishell.h"

char	*lst_find_env(char *key)
{
	t_env	*env;

	env = get_minish()->env;
	while (env->next)
	{
		if (ft_strequ(env->key, key))
			return (env->value);
		env = env->next;
	}
	return(NULL);
}

static int count_arg(char **argv)
{
	int i;

	i = 0;
	while (argv[i])
		i++;
	return (i);
}

void	exec_cd(t_cmd *cmd)
{
	char cwd[PATH_MAX];
	int cnt;
	char *value;

	cnt = count_arg(cmd->argv);
	if (cnt == 1)
		chdir("/");
	else if (cnt > 3)
		too_many_arg_error(cmd->argv[0], 0);
	else if (ft_strlen(cmd->argv[1]) > PATH_MAX)
		file_too_long(cmd->argv[0], cmd->argv[1], 0);
	else 
	{
		if (ft_strequ(cmd->argv[1], "~"))
			value = lst_find_env("HOME");
		else
			value = cmd->argv[1];
		if (chdir(value) == -1)
			no_file_error(cmd->argv[0], cmd->argv[1], 0);
		else
			lst_check_and_add_env("PWD", getcwd(cwd, sizeof(cwd)));
	}
}
