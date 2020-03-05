/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: froussel <froussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/24 18:53:24 by wpark             #+#    #+#             */
/*   Updated: 2020/03/05 13:42:39 by froussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int
	check_str_digit(char *s)
{
	while (s && *s)
	{
		if (!ft_isdigit(*s))
			return (0);
		s++;
	}
	return (1);
}

int
	exec_exit(t_cmd *cmd)
{
	int		cnt;
	int		fdigit;
	char	ret;

	cnt = count_arg(cmd->argv);
	fdigit = check_str_digit(cmd->argv[1]);
	if (cmd->argv[1])
	{
		if (!fdigit)
		{
			ft_putstr("exit\n");
			exit(numeric_arg_error(cmd->argv[0], cmd->argv[1], 2));
		}
		if (cnt > 2)
		{
			ft_putstr("exit\n");
			return (too_many_arg_error(cmd->argv[0], 1));
		}
		ret = (char)ft_atoi(cmd->argv[1]);
		free_all();
		exit(ret);
	}
	free_all();
	exit(EXIT_SUCCESS);
}
