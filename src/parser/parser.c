/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhivoto <mzhivoto@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 16:02:40 by mzhivoto          #+#    #+#             */
/*   Updated: 2025/04/20 20:07:01 by mzhivoto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	print_prompt(t_cmd_input *cmd)
{
	cmd->input = readline("minishell$ ");
	if (!cmd->input)
		return (-1);
	return (1);
}

void	process_one(char *input, char *output, int *i, int *j)
{
	output[(*j)++] = ' ';
	output[(*j)++] = input[*i];
	output[(*j)++] = ' ';
	(*i)++;
}

void	process_two(char *input, char *output, int *i, int *j)
{
	output[(*j)++] = ' ';
	output[(*j)++] = input[*i];
	output[(*j)++] = input[*i + 1];
	output[(*j)++] = ' ';
	(*i) += 2;
}

void	process_three(char *input, char *output, int *i, int *j)
{
	output[(*j)++] = ' ';
	output[(*j)++] = input[*i];
	output[(*j)++] = input[*i + 1];
	output[(*j)++] = input[*i + 2];
	output[(*j)++] = ' ';
	(*i) += 3;
}

int	is_single_op(char *input, int i)
{
	if (input[i] == '|' || input[i] == '&' || input[i] == '<'
		|| input[i] == '>')
		return (1);
	return (-1);
}

int	is_double_op(char *input, int i)
{
	if ((input[i] == '>' && input[i + 1] == '>') || (input[i] == '<'
		&& input[i + 1] == '<') || (input[i] == '&' && input[i + 1] == '&')
		|| (input[i] == '|' && input[i + 1] == '|'))
		return (1);
	return (-1);
}

int	is_triple_op(char *input, int i)
{
	if ((input[i] == '<' && input[i + 1] == '<' && input[i + 2] == '<'))
		return (1);
	return (-1);
}

char	*add_space(t_cmd_input *cmd)
{
	cmd->i = 0;
	cmd->j = 0;
	cmd->len = ft_strlen(cmd->input);
	cmd->spaced = malloc(cmd->len * 4 + 1);
	if (!cmd->spaced)
		return (NULL);
	while (cmd->i < cmd->len)
	{
		if (cmd->input[cmd->i] == '\'' || cmd->input[cmd->i] == '\"')
		{
			if (fmt_quotes(cmd->input, cmd->spaced, &cmd->i, &cmd->j, 1) == -1)
				break ;
		}
		if (cmd->i + 2 < cmd->len && is_triple_op(cmd->input, cmd->i) == 1)
			process_three(cmd->input, cmd->spaced, &cmd->i, &cmd->j);
		else if (cmd->i + 1 < cmd->len && is_double_op(cmd->input, cmd->i) == 1)
			process_two(cmd->input,  cmd->spaced, &cmd->i, &cmd->j);
		else if (is_single_op(cmd->input, cmd->i) == 1)
			process_one(cmd->input, cmd->spaced, &cmd->i, &cmd->j);
		else
			cmd->spaced[cmd->j++] = cmd->input[cmd->i++];
	}
	cmd->spaced[cmd->j] = '\0';
	return (cmd->spaced);
}

int	parsing(t_cmd_input *data)
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
