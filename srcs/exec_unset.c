#include "minishell.h"

int	exec_unset(t_cmd *cmd)
{
	int i;

	i = 1;
	while (cmd->argv[i])
	{
		lst_remove_env(cmd->argv[i]);
		i++;
	}
	return (EXIT_SUCCESS);
}