#include "minishell.h"

static int is_built_in(char *arg)
{
	char **btin_arr;
	int		i;

	btin_arr = get_built_in();
	i = 0;
	while (btin_arr[i])
	{
		if (ft_strequ(btin_arr[i], arg))
			return (i);
		i++;
	}
	return (-1);
}

static void exec_built_in(int btin_nb, t_cmd *cmd)
{
	if (btin_nb == 0)
	{
		// exec_echo();	
	}
	else if (btin_nb == 1)
	{
		// exec_cd();
	}
	else if (btin_nb == 2)
	{
		// exec_pwd();
	}
	else if (btin_nb == 3)
		exec_export(cmd);
	else if (btin_nb == 4)
		exec_unset(cmd);
	else if (btin_nb == 5)
		exec_env(cmd);
	else if (btin_nb == 6)
	{
		// exec_exit();
	}
}

void	exec_command(void)
{
	t_cmd* cmd;
	int		i;
	int		btin_nb;

	cmd = get_minish()->cmd;
	i = 0;
	while (cmd)
	{
		if (cmd->is_pipe)
		{
			// pipe (need to fork)
		}
		else
		{
			if ((btin_nb = is_built_in(cmd->argv[0])) != -1)
				exec_built_in(btin_nb, cmd);
			else
			{
				// non builtin function (need to fork)
			}
		}
		cmd = cmd->next;
	}
}