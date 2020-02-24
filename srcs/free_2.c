/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wpark <wpark@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/24 16:36:55 by wpark             #+#    #+#             */
/*   Updated: 2020/02/24 16:41:28 by wpark            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void
	free_env(void)
{
	t_env *env;
	t_env *tmp;

	env = get_minish()->env;		
	while (env)
	{
		tmp = env->next;
		free(env->key);
		free(env->value);
		free(env);
		env = tmp;
	}
}

void
	free_all(void)
{
	free_cmd();
	free_env();
}
