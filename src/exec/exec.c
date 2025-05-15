#include "minishell.h"


int	run_bltin(t_data *data, t_command *cmd)
{
	int i;
	char	**args;

	i = 0;
	args = cmd->args;
	while (i < 7)
	{
		if (data->cmd_names[i] && ft_strcmp(args[0], data->cmd_names[i]) == 0)
		{
			data->status = data->builtins[i](data, cmd);
			return (data->status);
		}
		i++;
	}
	printf("%s: command not found\n", cmd->args[0]);
	data->status = 127;
	return(127);
}
//command not found -> status changes to 127, but not exit bash

int	is_builtin(t_data *data, t_command *cmd)
{
	int		i;
	char	**args;

	i = 0;
	args = cmd->args;
	while (i < 7)
	{
		if (data->cmd_names[i] && ft_strcmp(args[0], data->cmd_names[i]) == 0)
			return (1);
		i++;
	}
	return (0);
}

int	execute(t_data *data, t_command *cmd)
{
	if (!cmd || !cmd->args || !cmd->args[0])
		return (0);
	if (cmd_list_size(cmd) == 1)
	{
		if (is_builtin(data, cmd))
			return (run_bltin(data, cmd));

		//find out what is it
		// char *path = find_exec_path(cmd->args[0], data->envp);
		// if (!path)
		// {
		// 	fprintf(stderr, "%s: command not found\n", cmd->args[0]);
		// 	data->status = 127;
		// 	return 127;
		// }

		// // Run the executable
		// execve(path, cmd->args, data->envp);
		// perror("execve"); // Only reached if execve fails
		// free(path);
		// data->status = 126;
		// return 126;
	}
	return (0);
}
