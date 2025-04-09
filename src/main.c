/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhivoto <mzhivoto@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 13:10:49 by mzhivoto          #+#    #+#             */
/*   Updated: 2025/04/09 17:51:10 by mzhivoto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// #include <unistd.h>
// #include <stdio.h> // for printf


int main(int ac, char **av, char **env)
{
	char *input;
	

	(void)av;
	(void)env;
	if (ac < 1)
		return 1;
	
	while (1)
	{
		input = readline("minishell$ ");

	 
		if (!input)
			continue;
		
		if (*input)
		{
			
			if (strcmp(input,"pwd") == 0)
				getpwd();
			add_history(input);
			//printf("this is your input%s\n", input);
		}
		
		free(input);
	}

	return 0;
}

// if input exists check it for errros and tokenize it with linked list