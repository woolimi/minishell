/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: froussel <froussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/12 18:11:12 by froussel          #+#    #+#             */
/*   Updated: 2020/02/14 15:43:45 by froussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		count_semicolon(char *line)
{
	int count;
	int i;

	i = -1;
	count = 0;
	while(line[++i])
	{
		if(line[i]  == '\"')
		{
			i++;
			while(line[i] != '\"' && line[i])
				i++;
			if(line[++i] == '\0')
				printf("QUOTES NEED TO BE CLOSE\n");
		}
		if(line[i] == "; <>|>>")
			count++;
		i++;
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
	printf("%d\n", i);
	/*
	tokens = (char **)malloc(sizeof(char *) * (i + 1));
	i = 0;
	pos = 0 ;
	start = 0;
	while(line[i])
	{
		if(line[i] == '\'' || line[i] == '\"')
		{
			i++;
			while(line[i] != '\'' && line[i] != '\"')
				i++;
		}
		if(line[i] == ';')
		{
			tokens[pos] = ft_substr(line, start, i);
			pos++;
			start = i + 1;
		}
	}
	tokens[pos] = ft_substr(line, start, i);
	tokens[pos + 1] = NULL;
	*/
	return(tokens);
}

int main()
{
	char **test;
	int i = 0;
	test = parse_semicolon("cat salut\";o;g; ;s;h;i;t\" tout; le monde je ;vais");
	/*while (test[i] != NULL)
	{
		printf("%s", test[i]);
		i++;
	}*/
}
/*
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
	printf("CMD=|%s|\n", cmd);
	printf("INFO=|%s|\n", info);
	free(cmd);
	free(info);

}
*/