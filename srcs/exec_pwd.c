/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pwd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wpark <wpark@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/22 21:33:56 by wpark             #+#    #+#             */
/*   Updated: 2020/02/22 21:34:02 by wpark            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int exec_pwd(t_cmd *cmd)
{
	char cwd[PATH_MAX];
	
	(void)cmd;
	if (!(getcwd(cwd, sizeof(cwd))))
	{
		ft_putstr_fd(strerror(errno), 2);
		return (EXIT_FAILURE);
	}
	ft_putstr(cwd);
	ft_putstr("\n");
	return (EXIT_SUCCESS);
}
