/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: froussel <froussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/15 15:52:42 by froussel          #+#    #+#             */
/*   Updated: 2020/03/05 10:42:03 by froussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	count_params(char *line)
{
	int i;
	int count;

	i = 0;
	count = 0;
	while (line[i])
	{
		if (!ft_haschr(SEP_SPACE, line[i]) && line[i])
		{
			count++;
			while (!ft_haschr(SEP_SPACE, line[i]) && line[i])
			{
				if ((i = jmp_quotes(line, i)) == -1)
					return (0);
				i++;
			}
		}
		if (ft_haschr(SEP, line[i]))
			count++;
		i += check_sep(line, i, 2);
	}
	return (count);
}

static char	*spliter(char *line, int goal)
{
	int i;
	int st;
	int count;

	i = 0;
	st = 0;
	count = 0;
	while (line[i])
	{
		if (!ft_haschr(SEP_SPACE, line[i]) && line[i] && ++count)
		{
			while (!ft_haschr(SEP_SPACE, line[i]) && line[i])
				i = jmp_quotes(line, i) + 1;
			if (count == goal)
				return (ft_strsub(line, st, i - st));
			st = i;
		}
		if (ft_haschr(SEP, line[i]) && ++count)
			if (count == goal)
				return (ft_strsub(line, st, i + check_sep(line, i, 1) - st));
		i += check_sep(line, i, 2);
		st = i;
	}
	return (NULL);
}

char		**lexing(char *line)
{
	char	**tokens;
	int		count;
	int		i;

	i = -1;
	count = count_params(line);
	if (!(tokens = (char **)malloc(sizeof(char *) * (count + 1))))
		return (NULL);
	while (++i < count)
		tokens[i] = spliter(line, i + 1);
	tokens[i] = NULL;
	return (tokens);
}
