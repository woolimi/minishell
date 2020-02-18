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
	int cnt;

	if (cmd->is_rdir)
	{
		// dup, dup2
	}
	cnt = count_arg(cmd->argv);
	if (cnt == 1)
		chdir("/");
	else if (cnt > 3)
		too_many_arg_error(cmd->argv[0], 0);
	else
	{
		if (chdir(cmd->argv[1]) == -1)
		{
			no_file_error(cmd->argv[0], cmd->argv[1], 0);
		}
	}
	// update_env_pwd();
	// backup dup, dup2
}