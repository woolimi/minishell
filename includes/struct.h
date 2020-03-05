/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: froussel <froussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/24 19:44:45 by wpark             #+#    #+#             */
/*   Updated: 2020/03/05 13:34:42 by froussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

typedef struct		s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}					t_env;

typedef struct		s_rdir
{
	char			*file;
	int				fd;
	int				save_fd;
}					t_rdir;

typedef struct		s_cmd
{
	char			**argv;
	int				is_pipe;
	int				is_rdir;
	int				has_path;
	t_rdir			*in;
	t_rdir			*out;
	t_rdir			*out_dbl;
	struct s_cmd	*next;
}					t_cmd;

typedef struct		s_minish
{
	char			*line;
	char			**tokens;
	t_env			*env;
	t_cmd			*cmd;
	int				executed;
	int				excode;
}					t_minish;

#endif
