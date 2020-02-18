#include "minishell.h"

void exec_pwd(t_cmd *cmd)
{
	t_env *env;
	char buff[1024];

	if (cmd->is_rdir)
	{
		// dup, dup2
	}
	getcwd(buff, 1024);
	ft_putstr(buff);
	ft_putstr("\n");
	// backup dup, dup2
}