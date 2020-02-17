#include "minishell.h"

int syntax_error(char *token, int ret)
{
	ft_putstr("minishell: syntax error near unexpected toekn ");
	ft_putstr("\'");
	ft_putstr(token);
	ft_putstr("\'\n");
	return (ret);
}