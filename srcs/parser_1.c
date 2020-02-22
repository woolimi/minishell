/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wpark <wpark@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/22 21:37:25 by wpark             #+#    #+#             */
/*   Updated: 2020/02/22 21:37:26 by wpark            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int is_redir(char *s)
{
	if (ft_strequ(s, "<"))
		return (1);
	if (ft_strequ(s, ">"))
		return (1);
	if (ft_strequ(s, ">>"))
		return (1);
	return (0);
}

static int check_redir(char **tokens)
{
	int i;
	int fredi;

	fredi = 0;
	i = 0;
	while (tokens[i])
	{
		if (is_redir(tokens[i]))
		{
			fredi++;
			if (fredi == 2)
				return (syntax_error(tokens[i], 0));
		}
		else if (fredi == 1 &&
			(ft_strequ(tokens[i], "|")
			|| ft_strequ(tokens[i], ";")))
			return (syntax_error(tokens[i], 0));
		else
			fredi = 0;
		i++;
	}
	if (i != 0 && is_redir(tokens[i - 1]))
		return (syntax_error("newline", 0));
	return (1);
}

static int check_pipe(char **tokens)
{
	int fpip;
	int i;

	fpip = 0;
	i = 0;
	while (tokens[i])
	{
		if (ft_strequ(tokens[i], "|"))
		{
			if (i == 0)
				return (syntax_error("|", 0));
			fpip++;
			if (fpip == 2)
				return (syntax_error("|", 0));
		}
		else if (fpip == 1 &&
			(is_redir(tokens[i])
			|| ft_strequ(tokens[i], ";")))
			return (syntax_error(tokens[i], 0));
		else
			fpip = 0;
		i++;
	}
	if (i != 0 && ft_strequ(tokens[i - 1], "|"))
		return (syntax_error("|", 0));
	return (1);
}

static int check_semi(char **tokens)
{
	int i;
	int fsemi;

	fsemi = 0;
	i = 0;
	while (tokens[i])
	{
		if (ft_strequ(tokens[i], ";"))
		{
			if (i == 0)
				return (syntax_error(";", 0));
			fsemi++;
			if (fsemi == 2)
				return (syntax_error(";", 0));
		}
		i++;
	}
	return (1);
}

int ck_tokens(char **tokens)
{
	if (check_redir(tokens)
		&& check_pipe(tokens) 
		&& check_semi(tokens))
		return (1);
	return (0);
}