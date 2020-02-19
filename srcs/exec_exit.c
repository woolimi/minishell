#include "minishell.h"

static int check_str_digit(char *s)
{
	while (s && *s)
	{
		if (!ft_isdigit(*s))
			return (0);
		s++;
	}
	return (1);
}

int exec_exit(t_cmd *cmd)
{
	t_env *env;
	int cnt;
	int fdigit;

	cnt = count_arg(cmd->argv);
	fdigit = check_str_digit(cmd->argv[1]);
	if (cmd->argv[1])
	{
		if (fdigit)
			exit(ft_atoi(cmd->argv[1]));
		else if (fdigit && cnt > 2)
			exit(too_many_arg_error(cmd->argv[0], 1));
		else
			exit(numeric_arg_error(cmd->argv[0], cmd->argv[1], 2));
	}
	exit(EXIT_SUCCESS);
}