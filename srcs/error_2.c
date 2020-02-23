/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wpark <wpark@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/22 21:32:26 by wpark             #+#    #+#             */
/*   Updated: 2020/02/22 21:32:27 by wpark            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int numeric_arg_error(char *cmd, char *file, int ret)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(file, 2);
	ft_putstr_fd(": numeric argument required\n", 2);
	return (ret);
}

void fatal_error(void)
{
	ft_putstr_fd("minishell: fatal error\n", 2);
	free_all();
	exit(EXIT_FAILURE);
}