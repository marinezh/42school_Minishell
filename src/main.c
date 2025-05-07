/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhivoto <mzhivoto@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 13:10:49 by mzhivoto          #+#    #+#             */
/*   Updated: 2025/05/07 14:37:35 by mzhivoto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	shell_loop(void)
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

	(void)av;
	(void)env;
	// for (int i = 0; env[i]; i++)
	// 	printf("%s\n", env[i]);
	if (ac < 1)
		return (1);
	shell_loop();
	return (0);
}
