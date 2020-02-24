#include "minishell.h"

/*
 ** args : { "export", "KEY1=value1", "KEY2=value2" } 
 */

static int
	idententifier_error(char *ident)
{
	ft_putstr_fd("minishell: export: '", 2);
	ft_putstr_fd(ident, 2);
	ft_putstr_fd("': not a valid identifier", 2);
	ft_putstr_fd("\n", 2);
	return (EXIT_FAILURE);
}

static void
	check_arg_and_export(t_cmd *cmd, int i, int *ret)
{
	int end;
	int copy;

	end = 0;
	copy = 1;
	*ret = EXIT_SUCCESS;
	if (ft_strchr(cmd->argv[i], '='))
	{
		if (cmd->argv[i][0] == '=' && !(copy = 0))
			*ret = idententifier_error(cmd->argv[i]);
		while (cmd->argv[i][end] != '=')
			if (cmd->argv[i][end++] == ' ' && !(copy = 0))
				*ret = idententifier_error(cmd->argv[i]);
		if (copy)
		{
			cmd->argv[i][end] = '\0';
			end++;
			lst_check_and_add_env(cmd->argv[i], &cmd->argv[i][end]);
		}
	}
}

int	exec_export(t_cmd *cmd)
{
	int i;
	int ret;

	i = 0;
	while (cmd->argv[++i])
		check_arg_and_export(cmd, i, &ret);
	return (ret);
}
