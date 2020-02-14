/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: froussel <froussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/12 13:29:00 by froussel          #+#    #+#             */
/*   Updated: 2020/02/14 15:14:27 by froussel         ###   ########.fr       */
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
	char **tokens;
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
		if (!check_is_valide_quote())
		{
			ft_puststr("QUOTES NEED TO BE CLOSE\n");
			continue ;
		}
		// ft_split(line, ';');
		tokens = lexing(line);
		// treat command
		free(line);
	}
	return(0);
}

" \""
"\" "
"\"\n"