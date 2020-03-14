/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wpark <wpark@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/24 10:19:16 by wpark             #+#    #+#             */
/*   Updated: 2020/03/14 18:32:36 by wpark            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int
	count_pipes(t_cmd *begin)
{
	int i;

	i = 0;
	while (begin)
	{
		if (begin->is_pipe)
			i++;
		else
			break ;
		begin = begin->next;
	}
	return (i);
}

static int
	create_pipes(int pipes[], int nb)
{
	int i;

	i = 0;
	while (i < nb)
	{
		if (pipe(pipes + (i * 2)) == -1)
			fatal_error_exit();
		i++;
	}
	return (1);
}

static void
	close_all(int pipes[], int nb)
{
	int i;

	i = 0;
	while (i < 2 * nb)
		close(pipes[i++]);
}

static void
	close_pipe_and_wait(int pipes[], int nb, int cpid[])
{
	int status;
	int	i;
	
	close_all(pipes, nb);
	i = 0;
	while (i < nb + 1)
	{
		waitpid(cpid[i], &status, 0);
		i++;
	}
	get_exit_code(status, NO_EXCODE);
}

static void
	dup2_and_close_pipe(int pipes[], int i, int nb)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	if (i < nb)
		dup2(pipes[i * 2 + 1], 1);
	if (i > 0)
		dup2(pipes[(i - 1) * 2], 0);
	close_all(pipes, nb);
}

t_cmd
	*piping(t_cmd *cmd)
{
	int pipes[count_pipes(cmd) * 2];
	int nb;
	int i;
	int btin_nb;
	int cpid[count_pipes(cmd) + 1];

	nb = count_pipes(cmd);
	if (!create_pipes(pipes, nb))
		return (0);
	i = 0;
	while (i < (nb + 1))
	{
		if ((cpid[i] = fork()) == 0)
		{
			dup2_and_close_pipe(pipes, i, nb);
			if ((btin_nb = is_built_in(cmd->argv[0])) != -1)
				exit(exec_built_in(btin_nb, cmd));
			exec_non_built_in(cmd);
		}
		else if (cpid[i] == -1)
			fatal_error_exit();
		cmd = cmd->next;
		i++;
	}
	close_pipe_and_wait(pipes, nb, cpid);
	return (cmd);
}
