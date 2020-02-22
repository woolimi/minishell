/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wpark <wpark@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/15 01:47:57 by wpark             #+#    #+#             */
/*   Updated: 2020/02/22 17:23:15 by wpark            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char *ft_strnew(void)
{
	char *ret;

	if (!(ret = (char *)malloc(sizeof(char))))
		return (0);
	ret[0] = '\0';
	return (ret);
}

static ssize_t pos_nl(char *s)
{
	ssize_t i;

	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}

static int free_cache(char **cache, int ret)
{
	if (*cache)
	{
		free(*cache);
		*cache = 0;
	}
	return (ret);
}

static int extract(char **line, char **cache, int idx)
{
	char *tmp;

	if (idx >= 0)
	{
		if (!(*line = ft_strsub(*cache, 0, idx)))
			return (free_cache(cache, -1));
		if (!(tmp = ft_strsub(*cache, idx + 1, ft_strlen(*cache) - idx - 1)))
			return (free_cache(cache, -1));
	}
	else
	{
		if (!(*line = ft_strsub(*cache, 0, ft_strlen(*cache))))
			return (free_cache(cache, -1));
		tmp = 0;
	}
	free_cache(cache, 0);
	if (tmp && *tmp == '\0')
	{
		free(tmp);
		tmp = 0;
	}
	*cache = tmp;
	return (1);
}

int get_next_line(int fd, char **line)
{
	ssize_t r_size;
	char buff[BS + 1];
	static char *cache;
	char *tmp;

	if (fd < 0 || !line)
		return (free_cache(&cache, -1));
	while ((r_size = read(fd, buff, BS)) > 0)
	{
		buff[r_size] = '\0';
		if (!(tmp = ft_strjoin(cache, buff)))
			return (free_cache(&cache, -1));
		free_cache(&cache, 0);
		cache = tmp;
		if (pos_nl(cache) != -1)
			break;
	}
	if (r_size < 0)
		return (free_cache(&cache, -1));
	if (r_size == 0 && (!cache || *cache == '\0') && (*line = ft_strnew()))
		return (free_cache(&cache, 0));
	return (extract(line, &cache, pos_nl(cache)));
}