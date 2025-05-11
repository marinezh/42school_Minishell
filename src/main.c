#include "minishell.h"

int	shell_loop(t_data	*data)
{
	t_cmd_input	cmd_input;
	//t_token		*tokens_lexer = NULL; //do i need this?
	t_token		*tokens = NULL;
	t_command	*commands;
	
	while (1)
	{
		if (print_prompt(&cmd_input) == -1)
			break;
		// tokens_lexer = run_lexer(&cmd_input); and this?
		tokens = tokenize_input(cmd_input.input);
		if (!tokens)
			continue;
		if (error_check(tokens))
		{
    		//free_tokens(tokens);
   			continue; // skip to next input
		}

		commands = parse_tokens(tokens);
		print_commands(commands);
		add_history(cmd_input.input);

		run_bltin(data, commands);
		// Cleanup
		//free(cmd_input.input);
		//free_tokens(tokens);  // Free the tokens list
        //free(args);  // Free the args array
        //free_command_list(commands);  // Free the commands list, need to create this function
	}
	return (0);
}
int	main(int ac, char **av, char **env)
{
	t_data	data;

	(void)av;
	// for (int i = 0; env[i]; i++)
	// 	printf("%s\n", env[i]);
	if (ac < 1)
		return (1);
	//init struct where env are stored
	init_data(&data, env);
	shell_loop(&data);
	//clean struct where env are stored
	free_env_list(data.envp_list);
	free_envp_array(data.envp);
	return (0);
}
