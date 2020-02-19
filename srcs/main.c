/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wpark <wpark@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/12 13:29:00 by froussel          #+#    #+#             */
/*   Updated: 2020/02/19 02:31:53 by wpark            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	prompt_msg(void)
{
	ft_putstr("\033[32mMINISHELL\033[0m$ ");
}

void	signal_handler(int signo)
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

int	main(int ac, char **av, char **env)
{
	char **tokens;
	int ret;
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
		minish->line = 0;
		if (!get_next_line(0, &(minish->line)))
		{
			ft_putstr("\n");
			exit(0);
		}
		tokens = lexing(minish->line);
		if (!init_cmd_list(tokens))
		{
			// free line, token, cmd
			continue ;
		}
		exec_command();
	}
	return(0);
}
