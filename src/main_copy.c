#include "minishell.h"

int	run_bltin(t_llist list, t_edata edata)
{
	int i;

	i = 0;
	if (ft_strcmp("cmd", list.value) == 0)
	{
		while (i < 7)
		{
			if (ft_strcmp(list.key, edata.cmd_names[i]) == 0)
				break ;
			i++;
		}
	}
	edata.builtins[i](NULL, edata);
	return(0);
}

int	main(int ac, char **av, char **env)
{
	t_data	data;
	t_edata	edata;
	t_llist list;

	(void)av;
	(void)env;
	if (ac < 1)
		return (1);
	init_data(&edata);
	while (1)
	{
		if (print_prompt(&data) < 0)
			continue ;

		list.key = data.input;
		list.value = "cmd";
		run_bltin(list, edata);
		// if (data.input)
		// {
		// 	if (strcmp(data.input, "pwd") == 0)
		// 		getpwd();
		// 	add_history(data.input);
		// 	// printf("this is your input%s\n", input);
		// }
		parsing(&data);
		free(data.input);
	}
	return (0);
}