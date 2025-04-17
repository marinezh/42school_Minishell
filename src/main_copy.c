#include "minishell.h"

// #include <unistd.h>

int	main(int ac, char **av, char **env)
{
	// t_data	data;

	(void)av;
	(void)env;
	if (ac < 1)
		return (1);

	while (*env)
	{
		printf("%s\n", *env);
		env++;
	}

	// while (1)
	// {
	// 	if (print_prompt(&data) < 0)
	// 		continue ;
	// 	if (data.input)
	// 	{
	// 		if (strcmp(data.input, "pwd") == 0)
	// 			getpwd();
	// 		add_history(data.input);
	// 		// printf("this is your input%s\n", input);
	// 	}
	// 	parsing(&data);
	// 	free(data.input);
	// }
	return (0);
}