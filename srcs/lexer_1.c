/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: froussel <froussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/15 15:52:42 by froussel          #+#    #+#             */
/*   Updated: 2020/02/15 16:27:17 by froussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
				i = jmp_quotes(line, i);
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

static char	*check_token(char *tk, char quote)
{
	char	*new_tk;
	int		size;
	int		i;
	int		j;

	i = -1;
	size = 0;
	while (tk[++i])
		if (tk[i] == quote)
			size++;
	if (!(new_tk = malloc(sizeof(char) * (ft_strlen(tk) - size + 1))))
		return (NULL);
	i = -1;
	j = -1;
	while (tk[++i])
		if (tk[i] != quote)
			new_tk[++j] = tk[i];
	new_tk[++j] = '\0';
	return (new_tk);
}

static char	**check_tokens(char **tks)
{
	char	*new_tk;
	int		i;
	int		j;

	i = 0;
	while (tks[i])
	{
		j = -1;
		while (tks[i][++j])
		{
			if (tks[i][j] == '\"' || tks[i][j] == '\'')
			{
				new_tk = check_token(tks[i], tks[i][j]);
				free(tks[i]);
				tks[i] = new_tk;
				break ;
			}
		}
		i++;
	}
	return (tks);
}

char		**lexing(char *line)
{
	char	**tokens;
	int		count;
	int		i;

	i = -1;
	count = count_params(line);
	if (!(tokens = (char **)malloc(sizeof(char *) * (count + 1))))
		printf("ERREUR DE MALLOC");
	while (++i < count)
		tokens[i] = spliter(line, i + 1);
	tokens[i] = NULL;
	tokens = check_tokens(tokens);
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
	tk = lexing("ifconfig -a | grep ether | sed \"s/ether //g\" | sed \"s/  //g\" | sed \"s/ //g\"");
	while(tk[i])
	{
		printf("i=%d (%s)\n", i, tk[i]);
		free(tk[i]);
		i++;
	}
	free(tk);
}
*/