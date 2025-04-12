/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhivoto <mzhivoto@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 13:10:49 by mzhivoto          #+#    #+#             */
/*   Updated: 2025/04/12 13:46:01 by mzhivoto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// #include <unistd.h>
// #include <stdio.h> // for printf




int main(int ac, char **av, char **env)
{
	t_data data;
	
	(void)av;
	(void)env;
	if (ac < 1)
		return 1;
	
	while (1)
	{
		if (print_prompt(&data) < 0)
			continue;
		
		if (data.input)
		{
			
			if (strcmp(data.input,"pwd") == 0)
				getpwd();
			add_history(data.input);
			//printf("this is your input%s\n", input);
		}
		parsing(&data);
		free(data.input);
	}

	
	return 0;
}

// if input exists check it for errros and tokenize it with linked list