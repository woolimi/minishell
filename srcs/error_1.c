/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wpark <wpark@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/22 21:32:49 by wpark             #+#    #+#             */
/*   Updated: 2020/02/22 22:33:42 by wpark            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int syntax_error(char *token, int ret)
{
	ft_putstr_fd("minishell: syntax error near unexpected token ", 2);
	ft_putstr_fd("\'", 2);
	ft_putstr_fd(token, 2);
	ft_putstr_fd("\'\n", 2);
	return (ret);
}

int no_exec_error(char *cmd, int ret)
{
	ft_putstr_fd("minishell: command not found: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd("\n", 2);
	return (ret);
}

int no_file_error(char *cmd, char *file, int ret)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd, 2);
	if (file)
	{
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(file, 2);
	}
	ft_putstr_fd(": No such file or directory\n", 2);
	return (ret);
}

int too_many_arg_error(char *cmd, int ret)
{
	ft_putstr_fd("minishell: too many arguments: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd("\n", 2);
	return (ret);
}

int file_too_long(char *cmd, char *file, int ret)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(file, 2);
	ft_putstr_fd(": File name too long\n", 2);
	return (ret);
}
<<<<<<< HEAD:srcs/error.c

int numeric_arg_error(char *cmd, char *file, int ret)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(file, 2);
	ft_putstr_fd(": numeric argument required\n", 2);
	return (ret);
}
=======
>>>>>>> d1a9bb4d632eb26a1515b2333beeff763da53b24:srcs/error_1.c
