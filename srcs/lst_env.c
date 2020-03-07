/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: froussel <froussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/24 17:18:22 by wpark             #+#    #+#             */
/*   Updated: 2020/03/07 12:22:14 by froussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env
	*lst_new_env(char *key, char *value)
{
	t_env	*new;

	new = malloc(sizeof(t_env));
	new->key = ft_strdup(key);
	if (value)
		new->value = ft_strdup(value);
	new->next = NULL;
	return (new);
}

t_env
	*lst_last_env(t_env *begin)
{
	while (begin->next)
		begin = begin->next;
	return (begin);
}

t_env
	*lst_add_env(t_env *begin, char *key, char *value)
{
	t_env	*last;

	last = lst_last_env(begin);
	last->next = lst_new_env(key, value);
	return (begin);
}

void
	lst_remove_env(char *key)
{
	t_env *bef;
	t_env *now;
	t_env *nxt;

	bef = 0;
	now = get_minish()->env;
	while (now)
	{
		nxt = now->next;
		if (ft_strequ(now->key, key))
		{
			if (bef)
				bef->next = nxt;
			else
				get_minish()->env = nxt;
			free(now->key);
			free(now->value);
			free(now);
			break ;
		}
		bef = now;
		now = nxt;
	}
}

void
	lst_check_and_add_env(char *key, char *value)
{
	t_env	*env;
	t_env	*last;

	env = get_minish()->env;
	while (env)
	{
		//ret = ft_strequ(env->key, key);
		if (ft_strequ(env->key, key))
		{
			if (env->value && value)
			{
				free(env->value);
				env->value = ft_strdup(value);
			}
			return ;
		}
		last = env;
		env = env->next;
	}
	last->next = lst_new_env(key, value);
}
