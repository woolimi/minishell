/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: froussel <froussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/12 13:29:00 by froussel          #+#    #+#             */
/*   Updated: 2020/03/08 18:05:45 by froussel         ###   ########.fr       */
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
	static int	ret;
	static int	eof;
	char *bef_line;
	char *new_line;
	
	t_minish	*minish;

	minish = get_minish();
	if (eof)
	{
		bef_line = minish->line;
		new_line = 0;
		ret = get_next_line(0, &new_line);
		minish->line = ft_strjoin(bef_line, new_line);
		free(bef_line);
		free(new_line);
		if (ret == -1)
			fatal_error_exit();
		if (ret > 0)
			eof = 0; // 엔터를 쳤을 경우
		if (ret == 0)
		{
			ft_putstr("  \b\b");
			return (0);
		}
	}
	else // 이전 라인이 eof 가 아닌 경우
	{
		ret = get_next_line(0, &(minish->line));
		if (ret == -1)
			fatal_error_exit();
		if ((ret == 0 && ft_strlen(minish->line)))
		{
			eof = 1; 
			ft_putstr("  \b\b");
			return (0);
		}
		if (ret == 0 && !ft_strlen(minish->line))
		{
			ft_putstr("  \b\b");
			eof_exit();
		}
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
