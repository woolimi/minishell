#include "minishell.h"

static int count_arg(char **argv)
{
	int i;

	i = 0;
	while (argv[i])
		i++;
	return (i);
}

static void print_arg(char **argv, int i, int cnt)
{
	while (argv[i])
	{
		ft_putstr(argv[i]);
		if (i < cnt - 1)
			ft_putstr(" ");
		i++;
	}
}

void	exec_echo(t_cmd *cmd)
{
	int i;
	int cnt;

	// redirection check
	// code ..
	cnt = count_arg(cmd->argv);
	if (cnt > 2 && ft_strequ(cmd->argv[1], "-n"))
		print_arg(cmd->argv, 2, cnt);
	else
	{
		print_arg(cmd->argv, 1, cnt);
		ft_putstr("\n");		
	}
	// restore redirection
}