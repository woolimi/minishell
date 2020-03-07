/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: froussel <froussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/15 15:52:34 by froussel          #+#    #+#             */
/*   Updated: 2020/03/07 15:42:00 by froussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int
	get_key(char key[], char *arg)
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

static int
	change_env_to_value(char *arg, char *buff, int *j)
{
	char	key[100];
	char	*value;
	char	*tmp;
	int		ret;

	ret = 0;
	if (*arg == '$' && *(arg + 1) == '?')
	{
		ret = 1;
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

static int
	check_backslash(char *tk, char *buff, int *j, int quotes)
{
	int ret;

	ret = 0;
	if (*tk == '\\' && quotes)
	{
		ret = 1;
		if (ft_haschr("$\'\"\\", tk[1]))
			buff[++*j] = *(++tk);
		else if (ft_haschr(WHITE_SPACE, tk[1]))
			buff[++*j] = conv_white_space(tk[1]);
		else
		{
			buff[++*j] = *tk;
			buff[++*j] = *(++tk);
		}
	}
	else if (*tk == '\\')
	{
		ret = 1;
		buff[++*j] = *(++tk);
	}
	else
		buff[++*j] = *tk;
	return (ret);
}

char
	*check_quote(char *tk, int i)
{
	char	buff[LINE_MAX];
	int		j;

	j = -1;
	ft_memset(buff, 0, LINE_MAX);
	while (tk[++i])
		if (tk[i] == '\'')
			while (tk[++i] != '\'')
				buff[++j] = tk[i];
		else if (tk[i] == '\"')
			while (tk[++i] != '\"')
				if (tk[i] == '$')
					i += change_env_to_value(&tk[i], buff, &j);
				else
					i += check_backslash(&tk[i], buff, &j, 1);
		else
		{
			if (tk[i] == '$')
				i += change_env_to_value(&tk[i], buff, &j);
			else
				i += check_backslash(&tk[i], buff, &j, 0);
		}
	buff[++j] = '\0';
	return (ft_strdup(buff));
}

int
	check_dollar(t_cmd *cmd)
{
	char	*old_arg;
	int		i;

	i = 0;
	while (cmd->argv[++i])
	{
		old_arg = cmd->argv[i];
		cmd->argv[i] = check_quote(cmd->argv[i], -1);
		free(old_arg);
	}
	if (!check_inrdir_dollar(cmd->in))
		return (0);
	if (!check_outrdir_dollar(cmd->out))
		return (0);
	return (1);
}
