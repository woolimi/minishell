#include "minishell.h"

void exec_exit(t_cmd *cmd)
{
	t_env *env;

	if (cmd->is_rdir)
	{
		// dup, dup2
	}
	exit(0);
	// backup dup, dup2
}