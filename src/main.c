#include "minishell.h"

int	read_prompt(t_cmd_input *cmd, t_data *data)
{
<<<<<<< HEAD
	// cmd->input = readline("minishell$ ");
=======
	cmd->input = readline("minishell$ ");
	if (g_sig_received)
	{
		g_sig_received = 0;
		data->status = ERR_INTERUPTED_SIGINT;
		if (cmd->input)
		{
			free(cmd->input);
			cmd->input = NULL;
		}
		return (-2);
	}
	if (!cmd->input)
	{
		printf("exit\n");
		return (-1);
	}
	if (cmd->input[0] == '\0')
	{
		data->status = 0;
		free(cmd->input);
		cmd->input = NULL;
		return (0);
	}
	return (1);
	///////////////////////////////////////////////////////
	// PART FOR BIG TESTER, COMMENT IT IF DON'T NEED
	// char *line;
	// if (isatty(STDIN_FILENO))
	// {
	// 	line = readline("minishell$ ");
	// }
	// else
	// {
	// 	line = get_next_line(STDIN_FILENO);
	// 	if (line)
	// 	{
	// 		// Remove trailing newline added by get_next_line
	// 		size_t len = ft_strlen(line);
	// 		if (len > 0 && line[len - 1] == '\n')
	// 			line[len - 1] = '\0';
	// 	}
	// }
	// // Handle EOF or Ctrl+D
	// if (!line)
	// {
	// 	if (isatty(STDIN_FILENO))
	// 		printf("exit\n");
	// 	return (-1);
	// }
>>>>>>> main
	// if (g_sig_received)
	// {
	// 	g_sig_received = 0;
    //     data->status = ERR_INTERUPTED_SIGINT;
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
	// 	data->status = 0;
	// 	free(cmd->input);
	// 	cmd->input = NULL;
	// 	return (0);
	// }
	//return (1);
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
	if (g_sig_received)
	{
		free(line);
		cmd->input = NULL;
		return (-2);
	}
	// Empty line (e.g., user just pressed Enter)
	if (line[0] == '\0')
	{
		data->status = 0;
		free(line);
		cmd->input = NULL;
		return (0);
	}
	cmd->input = line;
	return (1);
	// 	//END OF PART FOR BIG TESTER
	// 	///////////////////////////////////////////////////////////
}

t_command	*parse_input(t_command *commands, t_data *data, char *input)
{
	char	**split_input;
	t_token	*tokens;

	split_input = preprocess_input(input, data);
	if (!split_input)
		return (NULL);
	tokens = tokenize_input(split_input, data);
<<<<<<< HEAD
=======
	// print_tokens(tokens);
>>>>>>> main
	free_split_input(split_input);
	if (!tokens)
		return (NULL);
	if (error_check(tokens, data))
		return (free_tokens(tokens), NULL);
	if (expand_variables(tokens, data) == -1)
		return (free_tokens(tokens), NULL);
	if (handle_word_splitting(&tokens, data) == -1)
		return (free_tokens(tokens), NULL);
	delete_empty_tokens(&tokens);
	commands = parse_tokens(tokens, data);
	if (!commands)
		return (free_tokens(tokens), NULL);
<<<<<<< HEAD
	if (remove_quotes_from_command_args(commands, data) == -1)
		return (free_tokens(tokens),free_command_list(commands), NULL);
=======
	if (!remove_quotes_from_command_args(commands, data))
		return (free_tokens(tokens), free_command_list(commands), NULL);
	// printf("/////////////////////////////////\n");
	// print_commands(commands);
>>>>>>> main
	free_tokens(tokens);
	return (commands);
}

void	shell_loop(t_data *data, t_command **commands)
{
	t_cmd_input	cmd_input;
	int			prompt_res;

	ft_memset(&cmd_input, 0, sizeof(t_cmd_input));
	while (!data->exit_f)
	{
		g_sig_received = 0;
		prompt_res = read_prompt(&cmd_input, data);
		if (prompt_res == -1)
			break ;
		if (prompt_res == -2 || prompt_res == 0)
			continue ;
		if (cmd_input.input && cmd_input.input[0] != '\0')
			add_history(cmd_input.input);
		*commands = parse_input(*commands, data, cmd_input.input);
		free(cmd_input.input);
		if (!(*commands))
			continue ;
		execute(data, *commands);
		free_command_list(*commands);
	}
}

int	main(int ac, char **av, char **env)
{
	t_data		data;
	t_command	*commands;

	commands = NULL;
	(void)av;
	if (ac < 1)
		return (1);
	if (init_data(&data, env) != 0)
	{
		cleanup_data(&data);
		return (1);
	}
	set_prompt_signals();
	rl_event_hook = rl_signal_handler;
	shell_loop(&data, &commands);
	cleanup_data(&data);
	return (data.status);
}
