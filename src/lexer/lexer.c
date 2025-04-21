#include "minishell.h"

int	print_prompt(t_cmd_input *cmd)
{
	cmd->input = readline("minishell$ ");
	if (!cmd->input)
	{
		printf("exit\n");
		return (-1);
	}
	return (1);
}

char	*add_space(t_cmd_input *cmd)
{
	cmd->i = 0;
	cmd->j = 0;
	cmd->len = ft_strlen(cmd->input);
	cmd->spaced = malloc(cmd->len * SPACING_FACTOR + 1);
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
		else if (cmd->i + 1 < cmd->len && is_dbl_op(cmd->input, cmd->i) == 1)
			process_two(cmd->input, cmd->spaced, &cmd->i, &cmd->j);
		else if (is_single_op(cmd->input, cmd->i) == 1)
			process_one(cmd->input, cmd->spaced, &cmd->i, &cmd->j);
		else
			cmd->spaced[cmd->j++] = cmd->input[cmd->i++];
	}
	cmd->spaced[cmd->j] = '\0';
	return (cmd->spaced);
}

int	run_lexer(t_cmd_input *cmd)
{
	char	**tokens;
	char	*new_input;
	int		i;

	i = 0;
	new_input = add_space(cmd);
	printf("new input: %s\n", new_input);
	tokens = quote_safe_split(new_input, ' ');
	printf("%s\n", cmd->input);
	while (tokens[i])
	{
		printf("%s\n", tokens[i]);
		i++;
	}
	while (tokens[i])
		free(tokens[i++]);
	free(new_input);
	free(tokens);
	return (0);
}
