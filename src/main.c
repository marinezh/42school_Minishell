#include "minishell.h"

//declared JUST for MacOS
extern rl_hook_func_t	*rl_event_hook;

int	read_prompt(t_cmd_input *cmd, t_data *data)
{
	// cmd->input = readline("minishell$ ");
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

	tokens = NULL;
	split_input = preprocess_input(input, data);
	if (!split_input)
		return (NULL);
	tokens = tokenize_input(split_input, data);
	//print_tokens(tokens);
	free_split_input(split_input);
	if (!tokens)
		return (NULL);
	if (error_check(tokens, data))
		return (free_tokens(tokens), NULL);
	if (!expand_variables(tokens, data))
		return (free_tokens(tokens), NULL);
	tokens = handle_word_splitting(tokens, data);
	if (!tokens)
			return (free_tokens(tokens), NULL);
	delete_empty_tokens(&tokens);
	commands = parse_tokens(tokens, data);
	// print_commands(commands);
	if (!commands)
		return (free_tokens(tokens), NULL);
	if (!remove_quotes_from_command_args(commands, data))
		return (free_tokens(tokens), free_command_list(commands), NULL);
	//printf("/////////////////////////////////\n");
	//print_commands(commands);
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
		ft_putstr_fd("Error initializing shell environment\n", 2);
		return (1);
	}
	set_prompt_signals();
	rl_event_hook = rl_signal_handler;
	shell_loop(&data, &commands);
    cleanup_data(&data);
	return (data.status);
}
