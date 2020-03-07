/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_env_to_char.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wpark <wpark@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/07 12:53:49 by wpark             #+#    #+#             */
/*   Updated: 2020/03/07 13:04:45 by wpark            ###   ########.fr       */
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
		i++;
		env = env->next;
	}
	return (i);
}

char
	**lst_env_to_char (t_env *env)
{
	char	**res;
	char	*tmp;
	int 	i;

	if (!(res = malloc(sizeof(char*) * count_env(env))))
		return (NULL);
	i = 0;
	while (env)
	{
		if (!env->value)
			res[i] = ft_strjoin(env->key, "=");
		else
		{
			tmp = ft_strjoin(env->key, "=");
			res[i] = ft_strjoin(tmp, env->value);
			free(tmp); 
		}
		i++;
		env = env->next;
	}
	return (res);
}