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