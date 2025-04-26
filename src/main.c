/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhivoto <mzhivoto@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 13:10:49 by mzhivoto          #+#    #+#             */
/*   Updated: 2025/04/26 15:50:06 by mzhivoto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	shell_loop(void)
{
	t_cmd_input	cmd_input;
	char		**tokens;
	t_command	*commands;
	int i = 0;

	while (1)
	{
		if (print_prompt(&cmd_input) == -1)
			break;

		tokens = run_lexer(&cmd_input);
		if (!tokens)
			continue;
		while (tokens[i])
			printf("tokens %s\n", tokens[i++]);
		commands = parse_tokens(tokens);
		t_command *curr = commands;

		while (curr)
		{
			print_command_debug(curr);
			curr = curr->next;
		}
		// if (strcmp(cmd_input.input,"pwd") == 0) // after adding this one i have got a sig fault, need to check why
 		// 		getpwd();
		// add_history(cmd_input.input);
		
		// if (!commands)
		// {
		// 	// handle parse error, maybe print "syntax error"
		// 	free_tokens(tokens);
		// 	continue;
		// }

		//execute_commands(commands); future function

		// Cleanup
		//free_command_list(commands); future function
		//free_tokens(tokens);
		//free(cmd_input.input);
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

// if input exists check it for errros and tokenize it with linked list