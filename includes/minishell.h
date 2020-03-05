/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: froussel <froussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/12 18:11:12 by froussel          #+#    #+#             */
/*   Updated: 2020/03/05 13:34:15 by froussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define WHITE_SPACE " tnvfr"
# define SEP_SPACE " \t<>|;"
# define SEP "<>|;"
# define SPACE " \t"
# define PATH_MAX 1024
# define LINE_MAX 100024
# define NO_EXCODE -1
# define NO_STATUS -1

# include "../lib/libft/libft.h"
# include <unistd.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <signal.h>
# include <fcntl.h>
# include <string.h>
# include <errno.h>
# include "struct.h"

/*
**	get static
*/

t_minish	*get_minish(void);
char		**get_built_in(void);

/*
** errors
*/

int			syntax_error(char *token, int ret);
int			no_file_error(char *cmd, char *file, int ret);
int			no_command_error(char *cmd, int ret);
int			too_many_arg_error(char *cmd, int ret);
int			numeric_arg_error(char *cmd, char *file, int ret);
int			file_too_long(char *cmd, char *file, int ret);

/*
** quit
*/

void		fatal_error_exit(void);
void		eof_exit(void);
void		get_exit_code(int status, int excode);

/*
** built-in
*/

int			is_built_in(char *arg);
int			exec_built_in(int btin_nb, t_cmd *cmd);
int			exec_env(t_cmd *cmd);
int			exec_unset(t_cmd *cmd);
int			exec_export(t_cmd *cmd);
int			exec_exit(t_cmd *cmd);
int			exec_pwd(t_cmd *cmd);
int			exec_cd(t_cmd *cmd);
int			exec_echo(t_cmd *cmd);

/*
**	free
*/

void		free_env(void);
void		free_cmd(void);
void		free_all(void);

/*
**	lst_cmd
*/

int			init_cmd_list(char **tokens);
t_cmd		*lst_new_cmd(char *token);
t_cmd		*lst_add_cmd(t_cmd *begin, char *token);
t_cmd		*lst_last_cmd(t_cmd *cmd);

/*
**	lst_env
*/

void		init_env_list(char **env);
void		lst_remove_env(char *key);
void		lst_check_and_add_env(char *key, char *value);
t_env		*lst_add_env(t_env *begin, char *key, char *value);
t_env		*lst_new_env(char *key, char *value);

/*
**	exec command
*/

void		exec_command(void);
void		exec_non_built_in(t_cmd *cmd);

/*
**	exec_cd
*/

char		*lst_find_env(char *key);

/*
**	piping
*/

t_cmd		*piping(t_cmd *cmd);

/*
**	redirection
*/

int			redirection(t_cmd *cmd);
void		close_redirection(t_cmd *cmd);

/*
**	parsing
*/

int			is_redir(char *s);
int			ck_tokens(char **tokens);
int			count_arg(char **argv);

/*
**	lexer_1.c
*/

char		**lexing(char *line);

/*
**	lexer_2.c
*/

int			jump_space(char *line, int i, int jmp);
int			check_sep(char *line, int i, int use);
int			jmp_quotes(char *line, int i);

/*
**	dollar_quotes.c
*/

char		**check_dollar(char **tks);

#endif
