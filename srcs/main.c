/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wpark <wpark@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/12 13:29:00 by froussel          #+#    #+#             */
/*   Updated: 2020/02/17 05:04:35 by wpark            ###   ########.fr       */
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
		prompt_msg();
	}
}

/*
** SIGINT : detect cntl + c
*/

int	main(int ac, char **av, char **env)
{
	char **tokens;
	int ret;
	t_minish	*minish;

	if (!ac || !av || !env)
		return (0);
	minish = get_minish();
	init_env_list(env);
	while(1)
	{
		prompt_msg();
	//	signal(SIGINT, signal_handler);
		minish->line = 0;
		ret = get_next_line(0, &(minish->line));		
		tokens = ft_split(minish->line, ' ');
		if (!init_cmd_list(tokens))
		{
			// free line, token, cmd
			continue ;
		}
		exec_command();
	}
	return(0);
}