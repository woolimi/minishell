/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_unset.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wpark <wpark@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/22 21:33:57 by wpark             #+#    #+#             */
/*   Updated: 2020/02/22 21:34:03 by wpark            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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