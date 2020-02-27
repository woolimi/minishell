/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wpark <wpark@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/15 15:52:34 by froussel          #+#    #+#             */
/*   Updated: 2020/02/24 19:36:07 by wpark            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"//change me

static int	get_key(char key[], char *arg)
{
	int i;

	i = 0;
	while (arg[i] && arg[i] != ' ' && arg[i] != '$' && arg[i] != '\"')
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

static char	*create_unquotes(char *tk, char *new_tk)
{
	int	i;
	int	j;

	i = -1;
	j = -1;
	while (tk[++i])
	{
		if (tk[i] == '\'')
		{
			while (tk[++i] != '\'')
				new_tk[++j] = tk[i];
		}
		else if (tk[i] == '\"')
		{
			while (tk[++i] != '\"')
				new_tk[++j] = tk[i];
		}
		else
			new_tk[++j] = tk[i];
	}
	new_tk[++j] = '\0';
	return (new_tk);
}

static char	*unquotes_token(char *tk)
{
	int		i;
	int		count;
	char	*new_tk;
	
	i = -1;
	count = 0;
	while (tk[++i])
	{
		if (tk[i] == '\'' && ++count)
			while (tk[++i] != '\'');
		else if (tk[i] == '\"' && ++count)
			while (tk[++i] != '\"');
	}
	if (!(new_tk = malloc(sizeof(char) * (ft_strlen(tk) - count * 2 + 1))))
		return (NULL);
	return (create_unquotes(tk, new_tk));
}

char	**check_dollar(char **tks)
{
	char	*old_tk;
	int		i;

	i = 0;
	while (tks[++i])
	{
		if (ft_strrchr(tks[i], '$'))
		{
				/*dell me that
				old_tk = tks[i];
				tks[i] = unquotes_token(tks[i]);
				free(old_tk);*/

			old_tk = tks[i];
			tks[i] = change_env_to_value(tks[i]);
			free(old_tk);
		}
		if (ft_strrchr(tks[i], '\'') || ft_strrchr(tks[i], '\"'))
		{
			old_tk = tks[i];
			tks[i] = unquotes_token(tks[i]);
			free(old_tk);
		}
	}
	return (tks);
}

/*int main()
{
	printf("%s\n", check_dollar("mais nom cest pas possible"));
	printf("%s\n", check_dollar("mais nom cest pas possible"));
	printf("%s\n", check_dollar("mais nom cest pas possible"));
	printf("%s\n", check_dollar("mais nom cest pas possible"));
	printf("%s\n", check_dollar("mais nom cest pas possible"));
	printf("%s\n", check_dollar("mais nom cest pas possible"));
	printf("%s\n", check_dollar("mais nom cest pas possible"));
	printf("%s\n", check_dollar("mais nom cest pas possible"));
	printf("%s\n", check_dollar("mais nom cest pas possible"));
}*/


