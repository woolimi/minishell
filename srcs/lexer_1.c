/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: froussel <froussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/15 15:52:42 by froussel          #+#    #+#             */
/*   Updated: 2020/02/15 18:43:44 by froussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"//change me

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
/*
int main()
{ 
   char **tk;
   int i = 0;
//tk = lexing("file>tata");
//tk = lexing("cat salut\";o;g; ;s;h;i;t\" tout; le monde je ;vais");
//tk = lexing("echo dsf\"fds\"fds 	");
//tk = lexing("echo \"fsd   fds\" sfd 	; echo lol");
//tk = lexing("echo>>nana");
//tk = lexing("file>tata");
//tk = lexing("   file>>tata;  ");
//tk = lexing("> putain");
//tk = lexing("");
//tk = lexing("echo \"couc\"o\"\"");
//tk = lexing("echo \"'couc'\"o\"'\"");
//tk = lexing("e\"\"\"\"\"cho\" salut");
//tk = lexing("ifconfig -a | grep ether | sed \"s/ether //g\" | sed \"s/  //g\" | sed \"s/ //g\"");
//tk = lexing("ifconfig -a | grep ether | sed \"s/ether //g\" | sed s/  //g\" | sed \"s/ //g\"");
tk = lexing("echo lol\" mdr  coquinou \"\"  salut  paris  les looser  \"\' lose   lose  \'perdant endehor ");
//tk = lexing("echo \"couco\"");
while(tk[i])
{
printf("i=%d (%s)\n", i, tk[i]);
free(tk[i]);
i++;
}
free(tk);
}*/
