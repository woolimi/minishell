/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wpark <wpark@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/15 15:52:34 by froussel          #+#    #+#             */
/*   Updated: 2020/02/16 22:18:02 by wpark            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"//change me

static int	get_key(char key[], char *arg)
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

static char	*change_env_to_value(char *arg)
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

void	quotes_check(char **tks, int i, int j)
{	
	char	*new_tk;
	
	if (tks[i][j] == '\'')
	{
		new_tk = check_token(tks[i], tks[i][j]);
		free(tks[i]);
		tks[i] = new_tk;
	}
	else if (tks[i][j] == '\"')
	{
		new_tk = check_token(tks[i], tks[i][j]);
		free(tks[i]);
		tks[i] = change_env_to_value(new_tk);
		free(new_tk);
	}
}
