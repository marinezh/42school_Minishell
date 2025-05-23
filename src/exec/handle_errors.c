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

	printf("usage: ");
	i = 0;
	while (args[i])
	{
		printf("%s", args[i]);
		if (args[i + 1])
			printf(" ");
		i++;
	}
	printf("%s", msg);
}