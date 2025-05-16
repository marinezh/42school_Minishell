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
	return(-1);
}

