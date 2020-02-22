/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wpark <wpark@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/12 13:29:00 by froussel          #+#    #+#             */
/*   Updated: 2020/02/22 20:19:37 by wpark            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	prompt_msg(void)
{
	ft_putstr("\033[32mMINISHELL\033[0m$ ");
}

static void	signal_handler(int signo)
{
	if (signo == SIGINT)
	{
		ft_putstr("\n");
		if (get_minish()->executed == 1)
			get_minish()->executed = 0;
		else
			prompt_msg();
	} else if (signo == SIGQUIT)
	{
		if (get_minish()->executed == 1)
		{
			ft_putstr("\n");
			get_minish()->executed = 0;
		}
	}
}

static void read_line(void)
{
	t_minish *minish;
	int ret;

	minish = get_minish();
	minish->line = 0;
	ret = get_next_line(0, &(minish->line));
	if (ret == 0)
	{
		ft_putstr("\n");
		free_all();
		exit(EXIT_SUCCESS);
	}
	if (ret == -1)
		fatal_error();
}

int	main(int ac, char **av, char **env)
{
	t_minish	*minish;

	if (!ac || !av || !env)
		return (0);
	minish = get_minish();
	init_env_list(env);
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, signal_handler);
	while (1)
	{
		prompt_msg();
		read_line();
		if (!(minish->tokens = lexing(minish->line)))
			fatal_error();
		if (!init_cmd_list(minish->tokens))
		{
			free_cmd();
			continue ;
		}
		exec_command();
		free_cmd();
	}
	return(0);
}
