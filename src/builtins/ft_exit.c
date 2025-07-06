#include "minishell.h"

void	handle_numeric_arg_error(t_data * data, char *arg)
{
	data->exit_f = 1;
	data->status = ERR_INVALID_EXIT_CODE;
    ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
    ft_putstr_fd(arg, STDERR_FILENO);
    ft_putstr_fd(": numeric argument required\n", STDERR_FILENO);
}
long long process_string(char *str, int *error)
{
	int	digit;
	long long res;

	res = 0;
	while (*str)
	{
		if (*str && !ft_isdigit(*str))
		{
			*error = 1;
			return (0);
		}
		digit = *str - '0';
		if (res > ((LLONG_MAX - digit) / 10))
		{
			*error = 1;
			return (0);
		}
		res = res * 10 + digit;
		str++;
	}
	return (res);
}

long long custom_strtoll(char *str, int *error)
{
	long long	res;
	int			sign;

	sign = 1;
	*error = 0;

	while (*str == ' ' || *str == '\t')
		str++;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			sign *= -1;
		str++;
	}
	if (sign == -1 && ft_strcmp(str, "9223372036854775808") == 0)
		return (LLONG_MIN);
	res = process_string(str, error);
	res = res * sign;
	return (res);
}

int	ft_exit(t_data *data, t_command *cmd)
{
	long long	exit_code;
	int			error;

	printf("exit\n");
	if (count_args(cmd->args) == 1)
	{
		data->exit_f = 1;
		return (data->status);
	}
	error = 0;
	exit_code = custom_strtoll(cmd->args[1], &error);
	if (error)
	{
		handle_numeric_arg_error(data, cmd->args[1]);
		return(data->status);
	}
	if (count_args(cmd->args) > 2)
	{
		data->status = ERR_GENERIC;
		ft_putstr_fd("minishell: exit: too many arguments\n", STDERR_FILENO);
		return (data->status);
	}
	data->exit_f = 1;
	data->status = (unsigned short int)exit_code % 256;
	return(data->status);
}
