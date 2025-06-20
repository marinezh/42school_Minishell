#include "minishell.h"



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
		{
			data->status = 0;
			break ;
		}
		if (prompt_res == 0) //signal received or empty input
		{
			data->status = ERR_INTERUPTED_SIGINT;
			continue ;
		}
		// tokens_lexer = run_lexer(&cmd_input); and this?
		split_input = preprocess_input(cmd_input.input);
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
		//printf("PURE TOKENS\n");
		//print_tokens(tokens);
		//  files = parse_redir(tokens);
		//  print_files_nodes(files);
		if (error_check(tokens, data))
		{
			free_tokens(tokens);
			free(cmd_input.input);
			continue ; // skip to next input
		}
		expand_variables(tokens, data);
		printf("XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX\n");
		if (tokens->type == WORD || tokens->type == FILE_NAME)
		{
			print_tokens(tokens);
			//int i = 0;
			if(ft_strchr(tokens->value, ' '))
			{
				printf("XXX there is a space found XXX\n");

				char **split = quote_safe_split(tokens->value, ' ');
				t_token *new_tokens = create_token_list_from_split(split);
				free_split_input(split);

				t_token *old_next = tokens->next;

					// Replace current token with first of new list
				t_token *to_free = tokens;
				tokens = new_tokens;

					// Find end of new list and link rest
				t_token *last = new_tokens;
				while (last->next)
					last = last->next;
				last->next = old_next;

				free(to_free->value);
				free(to_free);

				print_tokens(tokens);
			}
		}
		//remove_outer_quotes(tokens);
		commands = parse_tokens(tokens);
		//print_commands(commands);
		remove_quotes_from_command_args(commands); // New function
		printf("/////////////////////\n");
		print_commands(commands);
		printf("/////////////////////\n");
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
