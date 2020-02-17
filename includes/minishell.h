/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wpark <wpark@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/12 18:11:12 by froussel          #+#    #+#             */
/*   Updated: 2020/02/17 17:06:30 by wpark            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#define SEP_SPACE " \t<>|;"
#define SEP "<>|;"
#define SPACE " \t"

# include "../lib/libft/libft.h"
# include <unistd.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <signal.h>
# include "woolim.h"


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
