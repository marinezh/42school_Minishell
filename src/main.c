/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhivoto <mzhivoto@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 13:10:49 by mzhivoto          #+#    #+#             */
/*   Updated: 2025/05/08 11:13:53 by mzhivoto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	shell_loop(t_data	*data)
{
	t_cmd_input	cmd_input;
	//t_token		*tokens_lexer = NULL; //need to fix this
	t_token		*tokens = NULL;
	t_command	*commands;
	//int i = 0;

	while (1)
	{
		if (print_prompt(&cmd_input) == -1)
			break;
		//print_tokens(tokens); 
		// tokens_lexer = run_lexer(&cmd_input); FIX THIS
		tokens = tokenize_input(cmd_input.input);
		if (!tokens)
			continue;
		//print_tokens(tokens);
		// while (tokens[i])
		// 	printf("tokens %s\n", tokens[i++]);
		commands = parse_tokens(tokens);
		//t_command *curr = commands;
		print_commands(commands);
		// while (curr)
		// {
		// 	//print_command_debug(curr);
		// 	print_commands(curr);
		// 	curr = curr->next;
		// }
		// if (strcmp(cmd_input.input,"pwd") == 0) // after adding this one i have got a sig fault, need to check why
 		// 		getpwd();
		add_history(cmd_input.input);

		// if (!commands)
		// {
		// 	// handle parse error, maybe print "syntax error"
		// 	free_tokens(tokens);
		// 	continue;
		// }

		//execute_commands(commands); future function
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
