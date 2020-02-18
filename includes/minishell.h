/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wpark <wpark@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/12 18:11:12 by froussel          #+#    #+#             */
/*   Updated: 2020/02/17 19:21:36 by wpark            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define SEP_SPACE " \t<>|;"
# define SEP "<>|;"
# define SPACE " \t"
# define PATH_MAX 1024

# include "../lib/libft/libft.h"
# include <unistd.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <signal.h>
# include <fcntl.h>
# include "woolim.h"
# include <string.h>
# include <errno.h>


//DEBUG
# include <stdio.h>


/*
**	lexer_1.c 
*/
char	**lexing(char *line);

/*
**	lexer_2.c 
*/
int		jump_space(char *line, int i, int jmp);
int		check_sep(char *line, int i, int use);
int		jmp_quotes(char *line, int i);

#endif
