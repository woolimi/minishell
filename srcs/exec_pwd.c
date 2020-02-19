#include "minishell.h"

int exec_pwd(t_cmd *cmd)
{
	char cwd[PATH_MAX];
	
	if (!(getcwd(cwd, sizeof(cwd))))
	{
		ft_putstr_fd(strerror(errno), 2);
		return (EXIT_FAILURE);
	}
	ft_putstr(cwd);
	ft_putstr("\n");
	return (EXIT_SUCCESS);
}
