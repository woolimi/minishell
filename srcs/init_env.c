/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wpark <wpark@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/22 20:32:52 by wpark             #+#    #+#             */
/*   Updated: 2020/02/22 21:40:31 by wpark            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_env_list(char **env)
{
	char		**cut;
	int			i;
	t_minish	*minish;

	minish = get_minish();
	minish->env = 0;
	i = 0;
	while (env[i])
	{
		cut = ft_split(env[i], '=');
		if (i == 0)
			minish->env = lst_new_env(cut[0], cut[1]);
		else
			lst_add_env(minish->env, cut[0], cut[1]);
		free(cut[0]);
		free(cut[1]);
		free(cut);
		i++;
	}
}
