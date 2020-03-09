/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_rdir_dollar.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wpark <wpark@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/06 14:15:47 by wpark             #+#    #+#             */
/*   Updated: 2020/03/09 20:28:36 by wpark            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int
	check_outrdir_dollar(t_rdir *out)
{
	char	*old_file;

	while (out)
	{
		old_file = out->file;
		out->file = check_quote(out->file, -1);
		free(old_file);
		if (out->is_dbl)
			out->fd = open(out->file, O_WRONLY | O_APPEND | O_CREAT, S_IRUSR
				| S_IRGRP | S_IWGRP | S_IWUSR);
		else
			out->fd = open(out->file, O_WRONLY | O_TRUNC | O_CREAT, S_IRUSR
				| S_IRGRP | S_IWGRP | S_IWUSR);
		if (out->fd < 0)
			return (0);
		if (out->next)
			close(out->fd);
		out = out->next;
	}
	return (1);
}

int
	check_inrdir_dollar(t_rdir *in)
{
	char	*old_file;

	while (in)
	{
		old_file = in->file;
		in->file = check_quote(in->file, -1);
		free(old_file);
		if ((in->fd = open(in->file, O_RDONLY)) < 0)
			return (no_file_error(NULL, in->file, 0));
		if (in->next)
			close(in->fd);
		in = in->next;
	}
	return (1);
}
