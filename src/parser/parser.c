/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhivoto <mzhivoto@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 16:02:40 by mzhivoto          #+#    #+#             */
/*   Updated: 2025/04/17 19:30:43 by mzhivoto         ###   ########.fr       */
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
void process_one(char *input, char *output, int *i, int *j)
{
	output[(*j)++] = ' ';
	output[(*j)++] = input[*i];
	output[(*j)++] = ' ';
	(*i)++;
}
void process_two(char *input, char *output, int *i, int *j)
{
	output[(*j)++] = ' ';
	output[(*j)++] = input[*i];
	output[(*j)++] = input[*i + 1];
	output[(*j)++] = ' ';
	(*i) += 2;
}
void process_three(char *input, char *output, int *i, int *j)
{
	output[(*j)++] = ' ';
	output[(*j)++] = input[*i];
	output[(*j)++] = input[*i + 1];
	output[(*j)++] = input[*i + 2];
	output[(*j)++] = ' ';
	(*i) += 3;
}

char	*add_space(t_data *data)
{
	int		i;
	int		j;
	char	*input;
	char	*new_input;

	input = data->input;
	data->len = ft_strlen(data->input);
	new_input = malloc(data->len * 4 + 1);
	i = 0;
	j = 0;
	while (i < data->len)
	{
		if (input[i] == '\'' || input[i] == '\"')
			if (process_quotes(input, new_input, &i, &j, 1) == -1)
				break ;
		
		if (i + 2 < data->len && (input[i] == '<' && input[i + 1] == '<'
				&& input[i + 2] == '<'))
			process_three(input, new_input, &i, &j);
		
		else if (i + 1 < data->len && ((input[i] == '>' && input[i + 1] == '>')
				|| (input[i] == '<' && input[i + 1] == '<') || (input[i] == '&'
					&& input[i + 1] == '&') || (input[i] == '|' && input[i
					+ 1] == '|')))
			process_two(input, new_input, &i, &j);
		
		else if (input[i] == '|' || input[i] == '&' || input[i] == '<'
			|| input[i] == '>')
			process_one(input, new_input, &i, &j);
		
		else
			new_input[j++] = input[i++];
		
	}
	new_input[j] = '\0';
	return (new_input);
}

int	parsing(t_data *data)
{
	char	**tokens;
	char	*new_input;
	int		i;

	i = 0;
	new_input = add_space(data);
	printf("new input: %s\n", new_input);
	tokens = ft_split_2(new_input, ' ');
	printf("%s\n", data->input);
	while (tokens[i])
	{
		printf("%s\n", tokens[i]);
		i++;
	}
	free(new_input);
	return (0);
}
