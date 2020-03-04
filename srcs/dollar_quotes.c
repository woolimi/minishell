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
	while (arg[i] && !ft_haschr(" $\"\'=\\", arg[i]))
	{
		key[i] = arg[i];
		i++;
	}
	key[i] = '\0';
	return (i);
}

static int	change_env_to_value(char *arg, char *buff, int *j)
{
	char	key[100];
	char	*value;
	char	*tmp;
	int		ret;

	ret = 1;
	if (*arg == '$' && *(arg + 1) == '?')
	{
		tmp = ft_itoa(get_minish()->excode);
		*j = ft_strlcat(buff, tmp, LINE_MAX) - 1;
		free(tmp);
	}
	else if (*arg == '$' && (!*(arg + 1) || *(arg + 1) == ' '))
		buff[++*j] = *arg;
	else
	{
		ret = get_key(key, ++arg);
		value = lst_find_env(key);
		*j = ft_strlcat(buff, value, LINE_MAX) - 1;
	}
	return (ret);
}

static int	check_backslash(char *tk, char *buff, int *j, int quotes)
{
	int ret;

	ret = 0;
	if (*tk == '\\' && quotes)
	{
		ret = 1;
		if (ft_haschr("$\'\"\\", tk[1]))
			buff[++*j] = *(++tk);
		else
		{
			buff[++*j] = *tk;
			buff[++*j] = *(++tk);
		}
	}
	else if (*tk == '\\' && !quotes)
	{
		ret = 1;
		buff[++*j] = *(++tk);
	}
	else
		buff[++*j] = *tk;
	return (ret);
}

static char	*check_quote(char *tk)
{
	char buff[LINE_MAX];
	int	i;
	int	j;

	i = -1;
	j = -1;
	ft_memset(buff, 0, LINE_MAX);
	while (tk[++i])
		if (tk[i] == '\'')
			while (tk[++i] != '\'')
				i += check_backslash(&tk[i], buff, &j, 0);
		else if (tk[i] == '\"')
			while (tk[++i] != '\"')
				if (tk[i] == '$')
					i += change_env_to_value(&tk[i], buff, &j);
				else
					i += check_backslash(&tk[i], buff, &j, 1);
		else
			if (tk[i] == '$')
				i += change_env_to_value(&tk[i], buff, &j);
			else
				i += check_backslash(&tk[i], buff, &j, 0);
	buff[++j] = '\0';
	return (ft_strdup(buff));
}

char	**check_dollar(char **args)
{
	char	*old_arg;
	int		i;

	i = 0;
	while (args[++i])
	{
		old_arg = args[i];
		args[i] = check_quote(args[i]);
		free(old_arg);
	}
	return (args);
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


