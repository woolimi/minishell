/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wpark <wpark@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/24 10:19:16 by wpark             #+#    #+#             */
/*   Updated: 2020/02/24 13:56:41 by wpark            ###   ########.fr       */
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
		{
			
		}; /* error pipe in errono */
		i++;
	}
	return (1);
}

void get_exit_code(int status, int excode)
{
	if (excode == -1)
	{
		if (WIFEXITED(status))
			get_minish()->excode = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			get_minish()->excode = 128 + WTERMSIG(status);
	}
	else
		get_minish()->excode = excode;	
}

static void
	close_pipe_and_wait(int pipes[], int i, int nb)
{
	int status;

	if (i < nb)
		close(pipes[i * 2 + 1]);
	if (i > 0)
		close(pipes[(i - 1) * 2]);
	wait(&status);
}

static void
	dup2_and_close_pipe(int pipes[], int i, int nb)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	if (i < nb)
	{
		dup2(pipes[i * 2 + 1], 1);
		close(pipes[i * 2 + 1]);
	}
	if (i > 0)
	{
		dup2(pipes[(i - 1) * 2], 0);
		close(pipes[(i - 1) * 2]);
	}
}

t_cmd *piping(t_cmd *cmd)
{
	int pipes[count_pipes(cmd) * 2];
	int nb;
	int i;
	int btin_nb;
	int cpid;
	
	nb = count_pipes(cmd);
	create_pipes(pipes, nb);
	i = 0;
	while (i < (nb + 1))
	{
		if ((cpid = fork()) == 0)
		{
			dup2_and_close_pipe(pipes, i, nb);
			if ((btin_nb = is_built_in(cmd->argv[0])) != -1)
				exit(exec_built_in(btin_nb, cmd));
			exec_non_built_in(cmd);
		}
		else if (cpid == -1)
			fatal_error_exit();
		cmd = cmd->next;
		close_pipe_and_wait(pipes, i++, nb);
	}
	return (cmd);
}