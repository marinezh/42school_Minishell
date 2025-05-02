#include "minishell.h"
#include "exec.h"

int	run_bltin(char **args, t_data *data)
{
	int i;

	i = 0;
	while (i < 7)
	{
		if (data->cmd_names[i] && ft_strcmp(args[0], data->cmd_names[i]) == 0)
		{
			data->builtins[i](data);
			return (0);
		}
		else
		{
			printf("builtin doesn't exit\n");
			return(1);
		}
		i++;
	}
	return(1);
}