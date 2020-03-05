/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: froussel <froussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/24 09:39:46 by wpark             #+#    #+#             */
/*   Updated: 2020/03/05 16:32:56 by froussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int
	is_built_in(char *arg)
{
	char	**btin_arr;
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

int
	exec_built_in(int btin_nb, t_cmd *cmd)
{
	int ret;

	ret = -1;
	check_dollar(cmd);
	if (!redirection(cmd))
		return (0);
	if (btin_nb == 0)
		ret = exec_echo(cmd);
	else if (btin_nb == 1)
		ret = exec_cd(cmd);
	else if (btin_nb == 2)
		ret = exec_pwd(cmd);
	else if (btin_nb == 3)
		ret = exec_export(cmd);
	else if (btin_nb == 4)
		ret = exec_unset(cmd);
	else if (btin_nb == 5)
		ret = exec_env(cmd);
	else if (btin_nb == 6)
		ret = exec_exit(cmd);
	close_redirection(cmd);
	return (ret);
}

static void
	non_built_in_fork_and_wait(t_cmd *cmd)
{
	int	child_pid;
	int	status;

	if ((child_pid = fork()) == -1)
		fatal_error_exit();
	else if (child_pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		exec_non_built_in(cmd);
	}
	else if (child_pid > 0)
	{
		wait(&status);
		get_exit_code(status, NO_EXCODE);
	}
}

void
	exec_command(void)
{
	t_cmd	*cmd;
	int		btin_nb;

	cmd = get_minish()->cmd;
	get_minish()->executed = 1;
	while (cmd)
	{
		if (cmd->is_pipe)
		{
			cmd = piping(cmd);
			continue ;
		}
		if ((btin_nb = is_built_in(cmd->argv[0])) != -1)
			get_exit_code(NO_STATUS, exec_built_in(btin_nb, cmd));
		else
			non_built_in_fork_and_wait(cmd);
		cmd = cmd->next;
	}
	get_minish()->executed = 0;
}
