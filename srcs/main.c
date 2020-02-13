/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wpark <wpark@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/12 13:29:00 by froussel          #+#    #+#             */
/*   Updated: 2020/02/13 03:20:32 by wpark            ###   ########.fr       */
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
	char *line;
	char **command;
	int ret;

	if (!ac || !av || !env)
		return (0);
	while(1)
	{
		prompt_msg();
		signal(SIGINT, signal_handler);
		line = 0;
		ret = get_next_line(&line);
		// treat command
		// ft_split(line, ';');
		command = ft_split(line, ' ');
		if (ft_strlen(command[0]) == 4 
			&& ft_strnstr(command[0], "exit", 4))
			break ;
		// treat command
		free(line);
	}
	return(0);
}
