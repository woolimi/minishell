#include "minishell.h"

static char **create_path_arr(void)
{
	t_env	*env;
	char *path_env;
	char **path_arr;

	env = get_minish()->env;
	path_env = 0;
	while (env)
	{
		if (ft_strequ(env->key, "PATH"))
			path_env = env->value;
		env = env->next;
	}
	if (!path_env)
		return (0);
	path_arr = ft_split(path_env, ':');
	return (path_arr);	
}

static void	free_path_arr(char **path_arr)
{
	int i;

	i = 0;
	while (path_arr[i])
	{
		free(path_arr[i]);
		i++;
	}
	free(path_arr);
}

void	exec_non_built_in(t_cmd *cmd)
{
	char **path_arr;
	char *path_cmd1;
	char *path_cmd2;
	int	i;
	
	if (cmd->is_rdir)
		redirection(cmd);
	if (!cmd->has_path)
	{
		path_arr = create_path_arr();
		i = 0;
		while (path_arr[i])
		{
			path_cmd1 = ft_strjoin(path_arr[i], "/");
			path_cmd2 = ft_strjoin(path_cmd1, cmd->argv[0]);
			execve(path_cmd2, cmd->argv, NULL);//if work: program stop and leaks issue ??:
			free(path_cmd1);
			free(path_cmd2);
			i++;
		}
		free_path_arr(path_arr);
		exit(no_exec_error(cmd->argv[0], 127));
	}
	else
	{
		execve(cmd->argv[0], cmd->argv, NULL);;//if work: program stop and leaks issue ??:
		exit(no_file_error(cmd->argv[0], NULL, 127));
	}
}
