/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: froussel <froussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/12 18:11:12 by froussel          #+#    #+#             */
/*   Updated: 2020/02/13 17:38:55 by froussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		count_semicolon(char *line)
{
	int count;

	count = 0;
	while(*line)
	{
		if(*line == '\'' || *line == '\"')
		{
			*line++;
			while(*line != '\'' && *line != '\"' && *line)
				*line++;
			if(*line == '\0')
				printf("QUOTES NEED TO BE CLOSE\n");
		}
		if(*line == ';')
			count++;
		*line++;
	}
	return(count);
}

char	**parse_semicolon(char *line)
{
	char	**tokens;
	int		i;
	int		pos;
	int		start;

	i = count_semicolon(line);
	tokens = (char **)malloc(sizeof(*char) * (i + 1));
	i = 0;
	pos = 0 ;
	start = 0;
	while(line[i])
	{
		if(line[i] == '\'' || line[i] == '\"')
			while(line[i] != '\'' && line[i] != '\"')
				i++;
		if(line[i] == ';')
		{
			tokens[pos] = ft_substr(line, start, i);
			pos++;
			start = i;
		}
	}
	tokens[pos] = ft_substr(line, start, i);
	tokens[pos + 1] = NULL;
	return(tokens);
}

void	lexer(char *line)
{
	int i;
	int start;
	char *cmd;
	char *info;

	i = 0;
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	start = i;
	while(line[i] != ' ' && line[i])
		i++;
	cmd = ft_substr(line, start, i);
	start = i;
	while (line[i] && line[i] != ';')
		i++;
	info = ft_substr(line, start, i);

	//if(line[i] == ';')
	//	lexer(&line[i]);
	
	//DEBUG
	/*
	printf("CMD=|%s|\n", cmd);
	printf("INFO=|%s|\n", info);
	free(cmd);
	free(info);
	*/
}
