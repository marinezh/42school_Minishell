#include"minishell.h"

int	is_n_flag_valid(char *argv)
{
	int	i;

	i = 1;
	if (argv[0] != '-' || argv[1] == '\0')
		return (0);
	while(argv[i])
	{
		if (argv[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

int	ft_echo(t_data *data, t_command *cmd)
{
	int i;
	char	**argv;
	int n_flag;
	(void)data;

	argv = cmd->args;
	n_flag = 0;
	i = 1;
	while (argv[i] && is_n_flag_valid(argv[i]))
	{
		n_flag = 1;
		i++;
	}
	while (argv[i])
	{
		ft_putstr(argv[i]);
		if (argv[i + 1])
			ft_putchar(' ');
		i++;
	}
	if (!n_flag)
		ft_putchar('\n');
	return(0);
}