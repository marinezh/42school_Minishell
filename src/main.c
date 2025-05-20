#include "minishell.h"

int	shell_loop(t_data *data)
{
	t_cmd_input	cmd_input;
	t_token		*tokens;
	t_command	*commands;

	// t_token		*tokens_lexer = NULL; //do i need this?
	tokens = NULL;
	// t_files		*files;
	while (!data->exit_f)
	{
		if (print_prompt(&cmd_input) == -1)
			break ;
		// tokens_lexer = run_lexer(&cmd_input); and this?
		tokens = tokenize_input(cmd_input.input);
		if (!tokens)
			continue ;
		// print_tokens(tokens);
		//  files = parse_redir(tokens);
		//  print_files_nodes(files);
		if (error_check(tokens))
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
		free_tokens(tokens);         // Free the tokens list
		free_command_list(commands); // Free the commands list
	}
	return (data->status);
}
int	main(int ac, char **av, char **env)
{
	t_data	data;
	int		exit_code;

	(void)av;
	if (ac < 1)
		return (1);
	// init struct where env are stored
	init_data(&data, env);
	exit_code = shell_loop(&data);
	// clean struct where env are stored
	free_env_list(data.envp_list);
	free_double_array(data.envp);
	return (exit_code);
}
