#include "minishell.h"

int handle_error_arg(t_data *data, char *arg, char *msg, int error_code)
{
	data->status = error_code;
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(arg, STDERR_FILENO);
	ft_putstr_fd(msg, STDERR_FILENO);
    return(data->status);
}

void	print_error_msg(char *cmd, char *msg)
{
    ft_putstr_fd("minishell: ", STDERR_FILENO);
    ft_putstr_fd(cmd, STDERR_FILENO);
    ft_putstr_fd(msg, STDERR_FILENO);
}

void	print_error(char **args, char *msg)
{
	int i;

	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd("usage: ", STDERR_FILENO);
	i = 0;
	while (args[i])
	{
		ft_putstr_fd(args[i], STDERR_FILENO);
		if (args[i + 1])
			ft_putstr_fd(" ", STDERR_FILENO);
		i++;
	}
	ft_putstr_fd(msg, STDERR_FILENO);
}