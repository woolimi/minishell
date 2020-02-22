/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wpark <wpark@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/15 15:52:34 by froussel          #+#    #+#             */
/*   Updated: 2020/02/22 21:36:54 by wpark            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		jump_space(char *line, int i, int jmp)
{
	i += jmp;
	while (line[i] == ' ' || line[i] == '\t')
	{
		i++;
		jmp++;
	}
	return (jmp);
}

int		check_sep(char *line, int i, int use)
{
	int jmp;

	if (line[i] == ' ' || line[i] == '\t')
		jmp = 1;
	else if (line[i] == '>' && line[i + 1] == '>')
		jmp = 2;
	else if (line[i] == '>')
		jmp = 1;
	else if (line[i] == '<')
		jmp = 1;
	else if (line[i] == '|')
		jmp = 1;
	else if (line[i] == ';')
		jmp = 1;
	else
		return (0);
	if (use == 1)
		return (jmp);
	else if (use == 2)
		return (jump_space(line, i, jmp));
	return (0);
}

int		jmp_quotes(char *line, int i)
{
	if (line[i] == '\"')
	{
		i++;
		while (line[i] != '\"' && line[i])
			i++;
		if (line[i] == '\0')
		{
			ft_putstr("QUOTES NEED TO BE CLOSE\n");
			return(-1);
		}
	}
	else if (line[i] == '\'')
	{
		i++;
		while (line[i] != '\'' && line[i])
			i++;
		if (line[i] == '\0')
		{
			ft_putstr("QUOTES NEED TO BE CLOSE\n");
			return(-1);
		}
	}
	return (i);
}
