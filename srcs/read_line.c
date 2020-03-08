/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wpark <wpark@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/08 19:00:17 by wpark             #+#    #+#             */
/*   Updated: 2020/03/08 19:13:58 by wpark            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int
	previous_is_eof(int *ret, int *eof)
{
	char		*bef_line;
	char		*new_line;
	t_minish	*minish;

	minish = get_minish();
	bef_line = minish->line;
	new_line = 0;
	if ((*ret = get_next_line(0, &new_line)) < 0)
		fatal_error_exit();
	if (!(minish->line = ft_strjoin(bef_line, new_line)))
		fatal_error_exit();
	free(bef_line);
	free(new_line);
	if (*ret > 0)
		*eof = 0;
	if (*ret == 0)
	{
		ft_putstr("  \b\b");
		return (0);
	}
	return (1);
}

static int
	current_line_handle(int *ret, int *eof)
{
	t_minish	*minish;
	
	minish = get_minish();
	*ret = get_next_line(0, &(minish->line));
	if (*ret == -1)
		fatal_error_exit();
	if ((*ret == 0 && ft_strlen(minish->line)))
	{
		*eof = 1;
		ft_putstr("  \b\b");
		return (0);
	}
	if (*ret == 0 && !ft_strlen(minish->line))
	{
		ft_putstr("  \b\b");
		eof_exit();
	}
	return (1);
}

int
	read_line(void)
{
	static int	ret;
	static int	eof;
	t_minish	*minish;

	minish = get_minish();
	if (eof)
	{
		if (!previous_is_eof(&ret, &eof))
			return (0);
	}
	else
	{
		if (!current_line_handle(&ret, &eof))
			return (0);
	}
	minish->tokens = lexing(minish->line);
	if (!minish->tokens)
		fatal_error_exit();
	return (1);
}