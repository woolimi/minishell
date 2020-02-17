#include "minishell.h"

static int count_pipes(t_cmd *begin)
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

static int	create_pipes(int pipes[], int nb)
{
	int i = 0;

	while (i < nb)
	{
		if (pipe(pipes + (i * 2)) == -1)
			return (0); /* error pipe in errono */
		i++;
	}
	return (1);
}

static void close_pipes(int pipes[], int nb)
{
	int i;

	i = 0;
	while (i < nb)
	{
		close(pipes[i]);
		i++;
	}
}

t_cmd *piping(t_cmd *cmd)
{
	int pipes[count_pipes(cmd) * 2];
	int nb;
	int i;
	int cpid;
	int btin_nb;
	int status;

	nb = count_pipes(cmd);
	create_pipes(pipes, nb);
	i = 0;
	while (i < nb)
	{
		if ((cpid = fork()) == -1)
		{
			/* fork error */
			break ;
		}
		else if (cpid == 0)
		{
			dup2(pipes[i * 2 + 1], 1);
			close_pipes(pipes, nb);
			if ((btin_nb = is_built_in(cmd->argv[0]) != -1))
			{
				/* execute built in */
				printf("built-in function\n");
				exit(0);
			}
			else
			{
				printf("here\n");
				exec_non_built_in(cmd);
			}
		}
		else
		{
			dup2(pipes[i * 2], 0);
			close_pipes(pipes, nb);
			wait(&status);
		}
		cmd = cmd->next;
		i++;
	}
	return (cmd);
}