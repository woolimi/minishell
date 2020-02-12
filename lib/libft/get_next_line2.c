#include "libft.h"

int lst_hasnl(t_cache *cache)
{
	while (cache)
	{
		if (ft_haschr(cache->content, '\n'))
			return (1);
		cache = cache->next;
	}
	return (0);
}

t_cache *lst_new(char *content)
{
	t_cache *new;

	new = malloc(sizeof(t_cache));
	if (!new)
		return (0);
	new->content = content;
	new->next = 0;
	return (new);
}

t_cache *lst_add(t_cache **cache, char *content)
{
	t_cache *tmp = *cache;

	if (!content)
		return (0);
	if (!tmp)
		return (*cache = lst_new(content));
	else
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = lst_new(content);
		return (tmp->next);
	}
}

int lst_length(t_cache *cache)
{
	int total = 0;
	int i;

	while (cache)
	{
		i = 0;
		while (cache->content[i] && cache->content[i] != '\n')
			i++;
		total += i;
		if (cache->content[i] == '\n')
			return (total);
		cache = cache->next;
	}
	return (total);
}
