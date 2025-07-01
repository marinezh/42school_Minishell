#include "minishell.h"

int	copy_qtd_seg(char *input, char *output, int *i, int *j)
{
	char	quote;

	quote = input[*i];
	output[*j] = input[*i];
	(*i)++;
	(*j)++;
	while (input[*i] && input[*i] != quote)
	{
		output[*j] = input[*i];
		(*i)++;
		(*j)++;
	}
	if (input[*i] != quote)
		return (-2);
	output[*j] = input[*i];
	(*i)++;
	(*j)++;
	return (1);
}



char	*add_space(t_cmd_input *cmd, t_data *data)
{
	cmd->i = 0;
	cmd->j = 0;
	cmd->len = ft_strlen(cmd->input);
	cmd->spaced = malloc(cmd->len * 10 + 1);
	if (!cmd->spaced)
		return (NULL);
	while (cmd->i < cmd->len)
	{
		if (cmd->input[cmd->i] == '\'' || cmd->input[cmd->i] == '\"')
		{
			if (copy_qtd_seg(cmd->input, cmd->spaced, &cmd->i, &cmd->j) == -2)
			{
				free(cmd->spaced);
				cmd->spaced = NULL;
				data->status = 2;
				return (NULL);
			}
			continue ;
		}
		if (cmd->i + 1 < cmd->len && is_dbl_op(cmd->input, cmd->i) == 1)
			process_two(cmd->input, cmd->spaced, &cmd->i, &cmd->j);
		else if (is_single_op(cmd->input, cmd->i) == 1)
			process_one(cmd->input, cmd->spaced, &cmd->i, &cmd->j);
		else
			cmd->spaced[cmd->j++] = cmd->input[cmd->i++];
	}
	cmd->spaced[cmd->j] = '\0';
	return (cmd->spaced);
}

char	**preprocess_input(char *input, t_data *data)
{
	t_cmd_input	cmd;
	char		*spaced;
	char		**split_input;

	ft_memset(&cmd, 0, sizeof(t_cmd_input));
	if (!input || input[0] == '\0')
	{
		data->status = 1; // Consider empty input as non-error (or choose 1)
		return (NULL);
	}
	cmd.input = input;
	spaced = add_space(&cmd, data);
	if (!spaced)
	{
		if (data->status == 2)
			printf("minishell: quotes not closed\n");
		else
		{
			printf("minishell: memory allocation error\n");
			data->status = ERR_GENERIC; // Only overwrite if not already 2
		}
		return (NULL);
	}
	split_input = quote_safe_split(spaced);
	free(spaced); // correct position of free spaced, not later
	if (!split_input)
	{
		printf("minishell: memory allocation error\n");
		data->status = ERR_GENERIC;
		return (NULL);
	}
	return (split_input);
}
// free(spaced);
	// FOR DEBUGGIN , delete later
	// for (int j = 0; split_input[j]; j++)
	// printf("token[%d] = [%s]\n", j, split_input[j]);