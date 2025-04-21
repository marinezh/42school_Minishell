/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhivoto <mzhivoto@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 13:10:49 by mzhivoto          #+#    #+#             */
/*   Updated: 2025/04/21 16:46:25 by mzhivoto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av, char **env)
{
	t_cmd_input	cmd;

	(void)av;
	(void)env;
	if (ac < 1)
		return (1);
	while (1)
	{
		if (print_prompt(&cmd) < 0)
			continue ;
		if (cmd.input)
		{
			if (strcmp(cmd.input, "pwd") == 0)
				getpwd();
			add_history(cmd.input);
			// printf("this is your input%s\n", input);
		}
		parsing(&cmd);
		free(cmd.input);
	}
	return (0);
}

// if input exists check it for errros and tokenize it with linked list