/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: froussel <froussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/24 16:36:09 by wpark             #+#    #+#             */
/*   Updated: 2020/03/05 14:18:15 by froussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void
	free_rdir(t_rdir *rdir)
{
	if (rdir)
	{
		free(rdir->file);
		free(rdir);
	}
}

static void
	free_tokens(void)
{
	char	**tokens;
	int		i;

	tokens = get_minish()->tokens;
	if (tokens)
	{
		i = 0;
		while (tokens[i])
			free(tokens[i++]);
		free(tokens);
		get_minish()->tokens = 0;
	}
}

static void
	free_line(void)
{
	char *line;

	line = get_minish()->line;
	if (line)
		free(line);
	get_minish()->line = 0;
}

void
	free_cmd(void)
{
	t_cmd	*cmd;
	t_cmd	*tmp;
	int		i;

	free_line();
	free_tokens();
	cmd = get_minish()->cmd;
	while (cmd)
	{
		tmp = cmd->next;
		if (cmd->argv)
		{
			i = -1;
			while (cmd->argv[++i])
				free(cmd->argv[i]);
			free(cmd->argv);
		}
		free_rdir(cmd->in);
		free_rdir(cmd->out);
		free_rdir(cmd->out_dbl);
		free(cmd);
		cmd = tmp;
	}
	get_minish()->cmd = 0;
}
