#include "minishell.h"

int	read_prompt(t_cmd_input *cmd)
{
	sig_received = 0;

	/////////////////////////////////////////////////////////////
	// THIS IS OUR MAIN 
	// cmd->input = readline("minishell$ ");
	// //char *check = ft_strdup(cmd->input);
	// //free(cmd->input);
	// //cmd->input = check;
	// if (sig_received)
	// {
	// 	if (cmd->input)
	// 	{
	// 		free(cmd->input);
	// 		cmd->input = NULL;
	// 	}
	// 	return (-2);
	// }
	// if (!cmd->input)
	// {
	// 	printf("exit\n");
	// 	return (-1);
	// }
	// if (cmd->input[0] == '\0')
	// {
	// 	free(cmd->input);
	// 	cmd->input = NULL;
	// 	return (0);
	// }
	///////////////////////////////////////////////////////
	// PART FOR BIG TESTER, COMMENT IT IF DON'T NEED
	char *line;
	if (isatty(STDIN_FILENO))
	{
		line = readline("minishell$ ");
	}
	else
	{
		line = get_next_line(STDIN_FILENO);
		if (line)
		{
			// Remove trailing newline added by get_next_line
			size_t len = ft_strlen(line);
			if (len > 0 && line[len - 1] == '\n')
				line[len - 1] = '\0';
		}
	}
	// Handle EOF or Ctrl+D
	if (!line)
	{
		if (isatty(STDIN_FILENO))
			printf("exit\n");
		return (-1);
	}
	if (sig_received)
	{
		free(line);
		cmd->input = NULL;
		return (-2);
	}
	// Empty line (e.g., user just pressed Enter)
	if (line[0] == '\0')
	{
		free(line);
		cmd->input = NULL;
		return (0);
	}
	cmd->input = line;
// 	//END OF PART FOR BIG TESTER
// 	///////////////////////////////////////////////////////////	
 	return (1);
}

void	shell_loop(t_data *data)
{
	t_cmd_input	cmd_input;
	t_token		*tokens = NULL;
	t_command	*commands = NULL;
	char **split_input = NULL;
	int		prompt_res;

	while (!data->exit_f)
	{
		prompt_res = read_prompt(&cmd_input);
		if (prompt_res == -1)  //EOF (Cntl + D)/ exit
			break ;
		if (prompt_res == -2) //signal received
		{
			data->status = ERR_INTERUPTED_SIGINT;
			continue ;
		}
		if (prompt_res == 0)
			continue ;
		// tokens_lexer = run_lexer(&cmd_input); and this?
		split_input = preprocess_input(cmd_input.input, data);
		if (!split_input) // This will be NULL if fmt_quotes found an error
		{
			free(cmd_input.input);
			continue;
		}
		tokens = tokenize_input(split_input);
		free_split_input(split_input); // after we tokenise we do not need split_input anymore
		if (!tokens)
		{
			free(cmd_input.input);
			continue;
		}
		// printf("PURE TOKENS\n");
		//print_tokens(tokens);
		//  files = parse_redir(tokens);
		//  print_files_nodes(files);
		if (error_check(tokens, data))
		{
			free_tokens(tokens);
			free(cmd_input.input);
			continue ; // skip to next input
		}
	
		if (!expand_variables(tokens, data, 1))
		{
			//fprintf(stderr, "Expansion failed due to memory error.\n");
    		//data->status = 1;
    		free_tokens(tokens);
    		free(cmd_input.input);
    		continue; // Skip to next prompt
		}
		tokens = handle_word_splitting(tokens);
		delete_empty_tokens(&tokens);
		//print_tokens(tokens);
		//remove_outer_quotes(tokens);
		commands = parse_tokens(tokens);
		//print_commands(commands);
		remove_quotes_from_command_args(commands); // New function
		// printf("/////////////////////\n");
		//print_commands(commands);
		// printf("/////////////////////\n");
		add_history(cmd_input.input);
		free(cmd_input.input);
		free_tokens(tokens);			// Free the tokens list
		execute(data, commands);
		free_command_list(commands);	// Free the commands list
	}
}

int	main(int ac, char **av, char **env)
{
	t_data	data;

	(void)av;
	if (ac < 1)
		return (1);
	// init struct where env are stored
	if (init_data(&data, env) != 0)
	{
		ft_putstr_fd("Error initializing shell environment\n", 2);
		return (1);
	}
	set_prompt_signals();
	shell_loop(&data);
	// clean struct where env are stored
	free_env_list(&data.envp_list);
	free_double_array(data.envp);
	//rl_clear_history();
	return (data.status);
}
