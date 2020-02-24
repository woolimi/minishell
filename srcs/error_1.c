/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wpark <wpark@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/24 09:21:55 by wpark             #+#    #+#             */
/*   Updated: 2020/02/24 16:06:49 by wpark            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int
	syntax_error(char *token, int ret)
{
	ft_putstr_fd("minishell: syntax error near unexpected token ", 2);
	ft_putstr_fd("\'", 2);
	ft_putstr_fd(token, 2);
	ft_putstr_fd("\'\n", 2);
	return (ret);
}

int
	no_command_error(char *cmd, int ret)
{
	ft_putstr_fd("minishell: command not found: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd("\n", 2);
	return (ret);
}

int
	too_many_arg_error(char *cmd, int ret)
{
	ft_putstr_fd("minishell: too many arguments: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd("\n", 2);
	return (ret);
}
