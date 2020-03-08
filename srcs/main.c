/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: froussel <froussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/12 13:29:00 by froussel          #+#    #+#             */
/*   Updated: 2020/03/07 16:46:59 by froussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void
	prompt_msg(void)
{
	if (!get_minish()->line)
		ft_putstr("\033[32mMINISHELL\033[0m$ ");
}

void
	signal_handler(int signo)
{
	if (signo == SIGINT)
	{
		if (get_minish()->executed == 1)
		{
			ft_putstr("\n");
			get_minish()->executed = 0;
		}
		else
		{
			ft_putstr("\b\b  \b\b\n");
			prompt_msg();
			get_minish()->excode = 1;
		}
	}
	else if (signo == SIGQUIT)
	{
		if (get_minish()->executed == 1)
		{
			ft_putstr("Quit (core dumped)\n");
			get_minish()->executed = 0;
		}
	}
}

static int
	read_line(void)
{
	int			ret;
	t_minish	*minish;

	minish = get_minish();
	minish->line = 0;
	ret = get_next_line(0, &(minish->line));
	//printf("len : %zu\n", ft_strlen(minish->line));
	if (ret == -1)
		fatal_error_exit();
	if ((ret == 0 && ft_strlen(minish->line)))
	{
		printf("line=%s\n", minish->line);
		// ft_putstr("  \b\b\b");
		return (0);
	}
	if (ret == 0 && !ft_strlen(minish->line))
	{
		ft_putstr("here\n");
		eof_exit();
	}
	minish->tokens = lexing(minish->line);
	if (!minish->tokens)
		fatal_error_exit();
	return (1);
}

int
	main(int ac, char **av, char **env)
{
	if (!ac || !av || !env)
		return (0);
	init_env_list(env);
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, signal_handler);
	while (1)
	{
		prompt_msg();
		if (!read_line())
			continue ;
		if (!init_cmd_list(get_minish()->tokens))
		{
			free_cmd();
			continue ;
		}
		exec_command();
		free_cmd();
	}
	return (0);
}
