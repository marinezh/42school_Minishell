/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhivoto <mzhivoto@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 16:02:40 by mzhivoto          #+#    #+#             */
/*   Updated: 2025/04/13 17:26:14 by mzhivoto         ###   ########.fr       */
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
// char *check_quotes(t_data *data)
// {
// 	//data->len = ft_strlen(data->input);
// 	char *input;
// 	char *new_input;
// 	int i = 0;
// 	int j = 0;
// 	input = data->input;

// 		if (input[i] == '\'')
// 		{
// 			new_input[j++] = input[i++];
// 			while (input[i] && input[i] != '\'')
// 			{
// 				new_input[j++] = input[i++];
// 				if (input[i] == '\'')
// 					printf("quotes error");
// 				else
// 					new_input[j++] = input[i++];
// 			}

// 		}
// 	return new_input;
// }

char *add_space(t_data *data)
{
	int i;
	int j;
	char *input;
	char *new_input;
	
	input = data->input;
	data->len = ft_strlen(data->input);
	new_input = malloc(data->len * 4 + 1);
	i = 0;
	j = 0;
	while(i < data->len)
	{
		check_quotes(data);
		// if (input[i] == '\'')
		// {
		// 	new_input[j++] = input[i++];
		// 	while(input[i] && input[i] != '\'')
		// 	{
		// 		new_input[j++] = input[i++];
		// 	}
		// 	if(input[i] != '\'')
		// 		printf("quotes not closed\n");
		// 	else
		// 		new_input[j++] = input[i++];
		// }
		// if (input[i] == '\"') // need to expand$
		// {
		// 	new_input[j++] = input[i++];
		// 	while(input[i] && input[i] != '\"')
		// 	{
		// 		new_input[j++] = input[i++];
		// 	}
		// 	if(input[i] != '\"')
		// 		printf("quotes not closed\n");
		// 	else
		// 		new_input[j++] = input[i++];
		// }
		
		if (i + 2 < data->len && (input[i] == '<' && input[i + 1] == '<' && input[i + 2] == '<'))
		{
			new_input[j++] = ' ';
			new_input[j++] = input[i];;
			new_input[j++] = input[i + 1];
			new_input[j++] = input[i + 2];
			new_input[j++] = ' ';
			i += 3;
		}
		else if (i + 1 < data->len && (
			(input[i] == '>' && input[i + 1] == '>') ||
			(input[i] == '<' && input[i + 1] == '<') ||
			(input[i] == '&' && input[i + 1] == '&') ||
			(input[i] == '|' && input[i + 1] == '|')))
		{
			new_input[j++] = ' ';
			new_input[j++] = input[i];
			new_input[j++] = input[i + 1];
			new_input[j++] = ' ';
			i += 2;
		}
		else if (input[i] == '|' || input[i] == '&'|| input[i] == '<' || input[i] == '>')
		{
			new_input[j++] = ' ';
			new_input[j++] = input[i];
			new_input[j++] = ' ';
			i++;
		}
		else
		{
			new_input[j++] = input[i];
			i++;
		}
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
	printf("new input: %s\n", new_input);
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
