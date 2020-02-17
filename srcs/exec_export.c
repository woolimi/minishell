#include "minishell.h"

/*
** args : { "export", "KEY1=value1", "KEY2=value2" } 
*/

void	exec_export(t_cmd *cmd)
{
	int i;
	char **cut;

	i = 1;
	while (cmd->argv[i])
	{		
		if (ft_strchr(cmd->argv[i], ' '))
		{
			// minishell: export: 'cmd->argv[i]': not a valide identifier
			return ;
		}
		if (cmd->argv[i][0] != '=' && ft_strchr(cmd->argv[i], '='))
		{
			cut = ft_split(cmd->argv[i], '=');
			lst_check_and_add_env(cut[0], cut[1]);
			free(cut);
			return ;
		}
	}
}