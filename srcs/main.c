/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wpark <wpark@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/12 13:29:00 by froussel          #+#    #+#             */
/*   Updated: 2020/03/09 15:18:15 by wpark            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void
	prompt_msg(void)
{
	if (get_minish()->eof == 0)
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
			get_minish()->eof = 0;
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
