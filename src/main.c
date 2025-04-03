/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhivoto <mzhivoto@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 13:10:49 by mzhivoto          #+#    #+#             */
/*   Updated: 2025/04/03 18:02:19 by mzhivoto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"


int main(int ac, char **av, char **env)
{
	char *input;

	(void)av;
	while (1)
	{
		input = readline("minishell$ ");

	 
		if (!input)
			continue;
		
		if (*input)
		{
			add_history(input);
			printf("%s\n", input);
		}
		free(input);
	}
	return 0;
}

// if input exists check it for errros and tokenize it with linked list