/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wpark <wpark@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/08 19:00:17 by wpark             #+#    #+#             */
/*   Updated: 2020/03/09 18:44:15 by wpark            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int
	previous_is_eof(void)
{
	char		*bef_line;
	char		*new_line;
	t_minish	*minish;

	minish = get_minish();
	new_line = 0;
	if ((minish->ret = get_next_line(0, &new_line)) < 0)
		fatal_error_exit();
	bef_line = minish->eof ? minish->line : "";
	if (!(minish->line = ft_strjoin(bef_line, new_line)))
		fatal_error_exit();
	if (minish->eof)
		free(bef_line);
	free(new_line);
	if (minish->ret > 0)
		minish->eof = 0;
	if (minish->ret == 0)
	{
		ft_putstr("  \b\b");
		return (0);
	}
	return (1);
}

static int
	current_line_handle(void)
{
	t_minish	*minish;

	minish = get_minish();
	minish->ret = get_next_line(0, &(minish->line));
	if (minish->ret == -1)
		fatal_error_exit();
	if ((minish->ret == 0 && ft_strlen(minish->line)))
	{
		minish->eof = 1;
		ft_putstr("  \b\b");
		return (0);
	}
	if (minish->ret == 0 && !ft_strlen(minish->line))
	{
		ft_putstr("  \b\b");
		eof_exit();
	}
	return (1);
}

int
	read_line(void)
{
	t_minish	*minish;

	minish = get_minish();
	if (minish->eof)
	{
		if (!previous_is_eof())
			return (0);
	}
	else
	{
		if (!current_line_handle())
			return (0);
	}
	minish->tokens = lexing(minish->line);
	if (!minish->tokens)
		fatal_error_exit();
	return (1);
}
