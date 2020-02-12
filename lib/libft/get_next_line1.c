#include "libft.h"

int free_cache(t_cache **cache, int ret)
{
	t_cache *tmp;
	t_cache *nxt;

	if (*cache)
	{
		tmp = *cache;
		while (tmp)
		{
			nxt = tmp->next;
			free(tmp->content);
			free(tmp);
			tmp = nxt;
		}
		*cache = 0;
	}
	return (ret);
}

int pull_content(char *content, int j)
{
	int i;

	i = 0;
	while (content[j])
		content[i++] = content[j++];
	content[i] = 0;
	return (1);
}

void	next_content(t_cache **cache)
{
	t_cache *nxt;

	nxt = (*cache)->next;
	free((*cache)->content);
	free((*cache));
	*cache = nxt;
}

int extract(t_cache **cache, char **line)
{
	int		len;
	int		i;
	int		j;

	len = lst_length(*cache);
	*line = malloc(len + 1);
	if (!*line)
		return (free_cache(cache, -1));
	(*line)[len] = 0;
	i = 0;
	while (*cache)
	{
		j = 0;
		while ((*cache)->content[j] && (*cache)->content[j] != '\n')
			(*line)[i++] = (*cache)->content[j++];
		if ((*cache)->content[j++] == '\n')
			return (pull_content((*cache)->content, j));
		else
			next_content(cache);
	}
	return (0);
}

int get_next_line(char **line)
{
	static t_cache	*cache;
	char			buff[BS + 1];
	int				r_size;

	cache = 0;
	if (!lst_hasnl(cache))
	{
		while ((r_size = read(0, buff, BS)) > 0)
		{
			buff[r_size] = 0;
			if (!(lst_add(&cache, ft_strdup(buff))))
				return (free_cache(&cache, -1));
			if (ft_haschr(buff, '\n'))
				break;
		}
	}
	return (extract(&cache, line));
}