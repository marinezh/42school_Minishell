#include"minishell.h"

int	count_args(char **args)
{
	int count;

	count = 0;
	while (args[count])
		count++;
	return (count);
}

int	ft_cd(t_data *data, t_command *cmd)
{
	// int	i;
	(void)data;
	int	arg_len;

	arg_len = count_args(cmd->args);
	if (arg_len > 2)
	{
		print_error_msg("cd", ERR_TOO_MANY_ARGS);
		return(ERROR_GENERIC);
	}
	return (0);
}