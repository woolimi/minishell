/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_env_to_char.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wpark <wpark@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/07 12:53:49 by wpark             #+#    #+#             */
/*   Updated: 2020/03/08 18:50:42 by wpark            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int
	count_env(t_env *env)
{
	int i;

	i = 0;
	while (env)
	{
		if (env->value)
			i++;
		env = env->next;
	}
	return (i);
}

char
	**lst_env_to_char(t_env *env)
{
	char	**res;
	char	*tmp;
	int		i;

	if (!(res = malloc(sizeof(char*) * (count_env(env) + 1))))
		return (NULL);
	i = 0;
	while (env)
	{
		if (!env->value)
		{
			env = env->next;
			continue ;
		}
		tmp = ft_strjoin(env->key, "=");
		res[i++] = ft_strjoin(tmp, env->value);
		free(tmp);
		env = env->next;
	}
	res[i] = 0;
	return (res);
}
