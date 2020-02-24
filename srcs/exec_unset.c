/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_unset.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wpark <wpark@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/24 16:34:45 by wpark             #+#    #+#             */
/*   Updated: 2020/02/24 19:38:42 by wpark            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**	always return 0
*/

int	exec_unset(t_cmd *cmd)
{
	int i;

	i = 1;
	while (cmd->argv[i])
	{
		lst_remove_env(cmd->argv[i]);
		i++;
	}
	return (EXIT_SUCCESS);
}
