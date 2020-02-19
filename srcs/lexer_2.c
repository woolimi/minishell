/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wpark <wpark@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/15 15:52:34 by froussel          #+#    #+#             */
/*   Updated: 2020/02/16 22:18:02 by wpark            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"//change me

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

static int get_key(char key[], char *arg)
{
	int i;

	i = 0;
	while (arg[i] && arg[i] != ' ' && arg[i] != '$')
	{
		key[i] = arg[i];
		i++;
	}
	key[i] = '\0';
	return (i);
}

char *change_env_to_value(char *arg)
{
	char buff[1024];
	char key[100];
	char *value;
	int i;

	ft_memset(buff, 0, 1024);
	i = 0;
	while (*arg)
	{
		if (*arg == '$' && *(arg + 1) == '?')
		{
			i = ft_strlcat(buff, ft_itoa(get_minish()->excode), sizeof(buff));
			arg += 2;
		}
		else if (*arg != '$' ||
			(*arg == '$' && (!*(arg + 1) || *(arg + 1) == ' ')))
			buff[i] = *arg++;
		else
		{
			arg += get_key(key, ++arg);
			value = lst_find_env(key);
			i = ft_strlcat(buff, value, sizeof(buff));
		}
		i++;
	}
	buff[i] = '\0';
	return ft_strdup(buff);
}
