/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wpark <wpark@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/22 21:33:44 by wpark             #+#    #+#             */
/*   Updated: 2020/02/22 21:33:45 by wpark            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	int ret;
	int cnt;
	int fdigit;

	cnt = count_arg(cmd->argv);
	fdigit = check_str_digit(cmd->argv[1]);
	if (cmd->argv[1])
	{
		if (fdigit)
			ret = ft_atoi(cmd->argv[1]);
		else if (fdigit && cnt > 2)
			ret = too_many_arg_error(cmd->argv[0], 1);
		else
			ret = numeric_arg_error(cmd->argv[0], cmd->argv[1], 2);
		free_all();
		exit(ret);
	}
	free_all();
	exit(EXIT_SUCCESS);
}
