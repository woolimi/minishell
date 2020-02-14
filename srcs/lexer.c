/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: froussel <froussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/12 18:11:12 by froussel          #+#    #+#             */
/*   Updated: 2020/02/14 18:50:50 by froussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

#define SEP_SPACE " \t<>|;"
#define SEP "<>|;"
#define SPACE " \t"

int jump_space(char *line, int i)
{
	int jmp;

	jmp = 1;
	while(line[i] == ' ' || line[i] == '\t')
	{
		i++;
		jmp++;
	}
	return(jmp);
}

int	check_sep(char *line, int i)
{
	if(line[i] == ' ' || line[i] == '\t')
		return(jump_space(line, i + 1));
	if(line[i] == '>' && line[i + 1] == '>')
		return(jump_space(line, i + 2));
	if(line[i] == '>')
		return(jump_space(line, i + 1));
	if(line[i] == '<')
		return(jump_space(line, i + 1));
	if(line[i] == '|')
		return(jump_space(line, i + 1));
	if(line[i] == ';')
		return(jump_space(line, i + 1));
	return(0);
}

int jmp_quotes(char *line, int i)
{
	if(line[i]  == '\"')
	{
		i++;
		while(line[i] != '\"' && line[i])
			i++;
		if(line[i + 1] == '\0')
			printf("QUOTES NEED TO BE CLOSE\n");
	}
	else if(line[i]  == '\'')
	{
		i++;
		while(line[i] != '\'' && line[i])
			i++;
		if(line[i + 1] == '\0')
			printf("SINGLE QUOTE NEED TO BE CLOSE\n");
	}
	return(i);
}

int count_params(char *line)
{
	int i;
	int count;

	i = 0;
	while(line[i])
	{
		if(!ft_haschr(SEP_SPACE, line[i]) && line[i])
		{
			count++;
			while(!ft_haschr(SEP_SPACE, line[i]) && line[i])
			{
				jmp_quotes(line, i);
				i++;
			}
		}
		if(ft_haschr(SEP, line[i]))
			count++;
		i += check_sep(line, i);
	}
	return(count);
}



/*
int jump_space(char *line, int i)
{
	int j;

	j = 1;
	while(line[i] == ' ' || line[i] == '\t')
	{
		i++;
		j++;
	}
	//if(!line[i])
	//	return(1);
	return(j);
}

int	check_sep(char *line, int i)
{
	if(line[i] == ' ' || line[i] == '\t')
		return(jump_space(line, i + 1));
	if(line[i] == '>' && line[i + 1] == '>')
		return(jump_space(line, i + 2));
	if(line[i] == '>')
		return(jump_space(line, i + 1));
	if(line[i] == '<')
		return(jump_space(line, i + 1));
	if(line[i] == '|')
		return(jump_space(line, i + 1));
	if(line[i] == ';')
		return(jump_space(line, i + 1));
	return(0);
}

int count_params(char *line)
{
	int i;
	int res;
	int count;

	count = 1;
	i = jump_space(line, 0) - 1;
	while(line[++i])
	{
		if(line[i]  == '\"') //same for '
		{
			i++;
			count++;
			while(line[i] != '\"' && line[i])
				i++;
			if(line[i++] == '\0')
				printf("QUOTES NEED TO BE CLOSE\n");
		}
		if((res = check_sep(line, i)) && ++count)
			i += res - 1;
	}
	return(count);                                                       
}
*/
/*
char *spliter(char **tokens)
{

}

char *lexing(char *line)
{
	char	**tokens;
	int		count;

	count = count_params(line);
	if(!(tokens = (char **)malloc(sizeof(char *) * (count + 1))))
		printf("ERREUR DE MALLOC");
	return(spliter(tokens));
}
*/
int main()
{
	int res;
	//res = count_params("cat salut\";o;g; ;s;h;i;t\" tout; le monde je ;vais");
	//res = count_params("     	  |     \"\"	");
	//res = count_params("echo dsf\"fds\"fds 	");
	//res = count_params("echo \"fsd   fds\" sfd 	; echo lol");
	//res = count_params("file>tata");
	//res = count_params("file>tata;");
	//res = count_params("> putain");
	res = count_params("");
	printf("res=%d\n", res);
}
