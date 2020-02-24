/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_static.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wpark <wpark@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/24 16:43:48 by wpark             #+#    #+#             */
/*   Updated: 2020/02/24 19:38:34 by wpark            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_minish
	*get_minish(void)
{
	static t_minish	minish;
		
	return (&minish);
}

char
	**get_built_in(void)
{
	static char* built_in[8] = {
		"echo",
		"cd",
		"pwd",
		"export",
		"unset",
		"env",
		"exit",
		NULL
	};
	return (built_in);
}
