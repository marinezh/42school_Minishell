#include "minishell.h"

void	shell_loop(t_data *data)
{
	t_cmd_input	cmd_input;
	t_token		*tokens = NULL;
	t_command	*commands = NULL;
	char **split_input = NULL;

	while (!data->exit_f)
	{
		if (print_prompt(&cmd_input) == -1)
			break ;
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
		printf("PURE TOKENS\n");
		print_tokens(tokens);
		//  files = parse_redir(tokens);
		//  print_files_nodes(files);
		if (error_check(tokens, data))
		{
			free_tokens(tokens);
			free(cmd_input.input);
			continue ; // skip to next input
		}
		commands = parse_tokens(tokens);
		print_commands(commands);
		add_history(cmd_input.input);
		execute(data, commands);
		// Cleanup
		free(cmd_input.input);
		free_tokens(tokens);			// Free the tokens list
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
	init_data(&data, env);
	shell_loop(&data);
	// clean struct where env are stored
	free_env_list(&data.envp_list);
	free_double_array(data.envp);
	return (data.status);
}
