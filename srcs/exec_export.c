#include "minishell.h"

/*
 ** args : { "export", "KEY1=value1", "KEY2=value2" } 
 */

int	exec_export(t_cmd *cmd)
{
	char *key;
	int i;
	int end;
	char *tmp;

	i = 1;
	/*while (cmd->argv[i])
	{
		end = 0;
		if (ft_strchr(cmd->argv[i], '='))
		{
			if (cmd->argv[i][0] == '=')
			{
				printf("bash: export: `==gots': not a valid identifier");
				return ;
			}
			while (cmd->argv[i][end] != '=')
			{
				if (cmd->argv[i][end] == ' ')
				{
					printf("bash: export: `cou cou=gots': not a valid identifier");
					return ;
				}
				end++;
			}
			cmd->argv[i][end] = '\0';
			end++;
			lst_check_and_add_env(cmd->argv[i], &cmd->argv[i][end]);
		}
		i++;
	}*/
	return (EXIT_SUCCESS);
}

