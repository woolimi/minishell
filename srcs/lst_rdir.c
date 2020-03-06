/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_rdir.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wpark <wpark@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/06 13:45:23 by wpark             #+#    #+#             */
/*   Updated: 2020/03/06 14:14:27 by wpark            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_rdir
	*lst_new_rdir(char *file, int is_dbl)
{
	t_rdir *new;

	new = malloc(sizeof(t_rdir));
	new->file = ft_strdup(file);
	new->std = -1;
	new->is_dbl = is_dbl;
	new->next = NULL;
	return (new);
}

t_rdir
	*lst_last_rdir(t_rdir *begin)
{
	while (begin->next)
		begin = begin->next;
	return (begin);
}

static t_rdir
	*lst_add_rdir(t_rdir *begin, char *file, int is_dbl)
{
	t_rdir *last;

	if (!begin)
		return (lst_new_rdir(file, is_dbl));
	last = lst_last_rdir(begin);
	last->next = lst_new_rdir(file, is_dbl);
	return (begin);
}

void
	lst_add_redir_cmd(t_cmd *cmd, char *redir, char *file)
{
	t_cmd *last;

	last = lst_last_cmd(cmd);
	last->is_rdir = 1;
	if (ft_strequ(redir, "<"))
		last->in = lst_add_rdir(last->in, file, 0);
	else if (ft_strequ(redir, ">"))
		last->out = lst_add_rdir(last->out, file, 0);
	else if (ft_strequ(redir, ">>"))
		last->out = lst_add_rdir(last->out, file, 1);
}
