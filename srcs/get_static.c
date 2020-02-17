#include "minishell.h"

t_minish *get_minish(void)
{
	static t_minish	minish;

	return (&minish);
}

char **get_built_in(void)
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