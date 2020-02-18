#include "minishell.h"

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
	t_env *env;
	char cwd[PATH_MAX];
	int cnt;

	cnt = count_arg(cmd->argv);
	if (cnt == 1)
		chdir("/");
	else if (cnt > 3)
		too_many_arg_error(cmd->argv[0], 0);
	else
	{
		if (chdir(cmd->argv[1]) == -1)
			no_file_error(cmd->argv[1], 0);
		else
			lst_check_and_add_env("PWD", getcwd(cwd, sizeof(cwd)));
	}
}
