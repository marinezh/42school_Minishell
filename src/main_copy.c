#include "minishell.h"

int	run_bltin(char *str_in, t_data *data)
{
	int i;

	i = 0;
	while (i < 7)
	{
		if (data->cmd_names[i] && ft_strcmp(str_in, data->cmd_names[i]) == 0)
		{
			data->builtins[i](data);
			return (0);
		}
		i++;
	}
	return(1);
}

int	main(int ac, char **av, char **env)
{
	t_cmd_input	cmd;
	t_data	data;

	(void)av;
	(void)env;
	(void)ac;
	init_data(&data, env);
	while (1)
	{
		if (print_prompt(&cmd) < 0)
			continue ;
		run_lexer(&cmd);
		run_bltin(cmd.input, &data);
		free(cmd.input);
	}

	return (0);
}