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

void	print_error(char *cmd, char *arg, char *msg)
{
    ft_putstr_fd("minishell: ", STDERR_FILENO);
    ft_putstr_fd(cmd, STDERR_FILENO);
	ft_putstr_fd(arg, STDERR_FILENO);
    ft_putstr_fd(msg, STDERR_FILENO);
}
