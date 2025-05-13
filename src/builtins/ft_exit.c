#include "minishell.h"

int	ft_exit(t_data *data, t_command *cmd)
{
	if (count_args(cmd->args) == 1)
	{
		printf("exit\n");
		data->exit_f = 1;
		return (data->status);
	}
	return(data->status);
}