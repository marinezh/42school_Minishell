/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhivoto <mzhivoto@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 16:02:40 by mzhivoto          #+#    #+#             */
/*   Updated: 2025/04/12 16:12:01 by mzhivoto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	print_prompt(t_data *data)
{
	data->input = readline("minishell$ ");
	if (!data->input)
		return (-1);
	return (1);
}

char *add_space(t_data *data)
{
	int i;
	int j;
	int len;
	char *input;
	char *new_input;
	
	input = data->input;
	len = ft_strlen(input);
	new_input = malloc(len * 3 + 1);
	i = 0;
	j = 0;
	while(i < len)
	{
		if (input[i] == '|' || input[i] == '&'|| input[i] == '>' || input[i] == '<')
		{
			new_input[j++] = ' ';
			new_input[j++] = input[i];
			new_input[j++] = ' ';
		}
		else
			new_input[j++] = input[i];
		i++;
	}
	new_input[j] = '\0';
	return new_input;
}

int	parsing(t_data *data)
{
	char **tokens;
	char *new_input;
	int i = 0;

	new_input = add_space(data);
	printf("new input %s\n", new_input);
	tokens = ft_split(new_input, ' ');
	

	printf("%s\n",data->input);
	while (tokens[i])
	{
		printf("%s\n",tokens[i]);
		i++;
	}
	free(new_input); 
	return (0);
}
