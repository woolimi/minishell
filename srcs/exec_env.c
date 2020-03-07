/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: froussel <froussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/24 16:15:01 by wpark             #+#    #+#             */
/*   Updated: 2020/03/07 11:34:15 by froussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void
	print_env(t_env *env)
{
	while (env)
	{
		if (env->value != NULL)
		{
			ft_putstr(env->key);
			ft_putstr("=");
			ft_putstr(env->value);
			ft_putstr("\n");
		}
		env = env->next;
	}
}

int
	exec_env(t_cmd *cmd)
{
	(void)cmd;
	print_env(get_minish()->env);
	return (EXIT_SUCCESS);
}
