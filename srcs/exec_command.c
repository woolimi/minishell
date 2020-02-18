#include "minishell.h"

int is_built_in(char *arg)
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
		exec_exit(cmd);
}

void	exec_command(void)
{
	t_cmd* cmd;
	int		btin_nb;
	int 	child_pid;
	int 	status;

	cmd = get_minish()->cmd;
	get_minish()->executed = 1;
	while (cmd)
	{
		if (cmd->is_pipe)
		{
			cmd = piping(cmd);
			continue ;
		}
		else
		{
			if ((btin_nb = is_built_in(cmd->argv[0])) != -1)
				exec_built_in(btin_nb, cmd);
			else
			{
				if ((child_pid = fork()) == -1)
				{ /* fork failed error */}
				else if (child_pid == 0)
					exec_non_built_in(cmd);
				else if (child_pid > 0)
					wait(&status);
			}
		}
		cmd = cmd->next;
	}
	get_minish()->executed = 0;
}