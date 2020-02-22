/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wpark <wpark@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/22 21:37:19 by wpark             #+#    #+#             */
/*   Updated: 2020/02/22 21:37:20 by wpark            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd *lst_new_cmd(char *token)
{
	t_cmd *new;

	new = malloc(sizeof(t_cmd));
	new->argv = malloc(sizeof(char*) * 2);
	new->argv[0] = ft_strdup(token);
	new->argv[1] = NULL;
	new->is_pipe = 0;
	new->is_rdir = 0;
	if (ft_strchr(new->argv[0], '/'))
		new->has_path = 1;
	else
		new->has_path = 0;	
	new->in = NULL;
	new->out = NULL;
	new->out_dbl = NULL;
	new->next = NULL;
	return (new);
}

t_cmd *lst_add_cmd(t_cmd *begin, char *token)
{
	t_cmd *tmp;

	if (!begin)
		return (lst_new_cmd(token));
	else
	{
		tmp = begin;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = lst_new_cmd(token);
	}
	return (begin);
}

t_cmd *lst_last_cmd(t_cmd *cmd)
{
	t_cmd *last;

	last = cmd;
	while (last->next)
		last = last->next;
	return (last);
}