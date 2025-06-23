#include "minishell.h"

int	copy_quoted_seg(char *input, char *output, int *i, int *j)
{
	char quote; 
	
	quote = input[*i]; 
	output[*j] = input[*i]; // copy openning quotes
	(*i)++;
	(*j)++;
	while (input[*i] && input[*i] != quote) // copy everything in qutes
	{
		output[*j] = input[*i];
		(*i)++;
		(*j)++;
	}
	if (input[*i] != quote)
	{
		ft_putstr_fd("minishell:quotes are not closed", 2);
		//ft_putstr_fd(ERR_QUOTES, 2);
		return (ERR_PARSER);
	}
	output[*j] = input[*i]; // copy closing quotes
	(*i)++;
	(*j)++;
	return (0);
}

void	add_space(t_cmd_input *cmd)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	cmd->len = ft_strlen(cmd->input);
	cmd->spaced = malloc(cmd->len * 10 + 1);
	if (!cmd->spaced)
		return ;
	while (i < cmd->len)
	{
		if (cmd->input[i] == '\'' || cmd->input[i] == '\"')
		{
			if (copy_quoted_seg(cmd->input, cmd->spaced, &i, &j) == -1)
			{
				free(cmd->spaced);
				cmd->spaced = NULL;
				return;
			}
			continue ;
		}
		if (i + 1 < cmd->len && is_dbl_op(cmd->input, i) == 1)
			process_two(cmd->input, cmd->spaced, &i, &j);
		else if (is_single_op(cmd->input, i) == 1)
			process_one(cmd->input, cmd->spaced, &i, &j);
		else
			cmd->spaced[j++] = cmd->input[i++];
	}
	cmd->spaced[j] = '\0';
	printf("DEBUG spaced: [%s]\n", cmd->spaced);
	// return (cmd->spaced);
}

// char	**run_lexer(t_cmd_input *cmd)
// {
// 	char	**tokens;
// 	char	*spaced_input;
// 	// int		i;
// 	// i = 0;

// 	spaced_input = add_space(cmd);
// 	if (!spaced_input)
// 		return (NULL);
// 	printf("%s\n", cmd->input);
// 	printf("new input: %s\n", spaced_input);
// 	tokens = quote_safe_split(spaced_input, ' ');

// 	// while (tokens[i])
// 	// {
// 	// 	printf("%s\n", tokens[i]);
// 	// 	i++;
// 	// }
// 	return (tokens);
// }
