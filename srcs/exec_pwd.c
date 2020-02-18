#include "minishell.h"

void exec_pwd(t_cmd *cmd)
{
	t_env *env;
	char buff[1024];
	
	getcwd(buff, 1024);//Null if fail with errno i
	ft_putstr(buff);
	ft_putstr("\n");
}
