#include "minishell.h"

void eof_exit(void)
{
	ft_putstr("\n");
	free_all();
	exit(0);
}

void fatal_error_exit(void)
{
	ft_putstr_fd("minishell: fatal error\n", 2);
	free_all();
	exit(EXIT_FAILURE);
}
