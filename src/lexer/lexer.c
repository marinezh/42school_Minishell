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

void	add_space(t_cmd_input *cmd)
{
	cmd->i = 0;
	cmd->j = 0;
	cmd->len = ft_strlen(cmd->input);
	cmd->spaced = malloc(cmd->len * 10 + 1);
	if (!cmd->spaced)
		return ;
	while (cmd->i < cmd->len)
	{
		if (cmd->input[cmd->i] == '\'' || cmd->input[cmd->i] == '\"')
		{
			if (fmt_quotes(cmd->input, cmd->spaced, &cmd->i, &cmd->j, 1) == -1)
				break ;
			continue;
		}
		if (cmd->i + 1 < cmd->len && is_dbl_op(cmd->input, cmd->i) == 1)
			process_two(cmd->input, cmd->spaced, &cmd->i, &cmd->j);
		else if (is_single_op(cmd->input, cmd->i) == 1)
			process_one(cmd->input, cmd->spaced, &cmd->i, &cmd->j);
		else
			cmd->spaced[cmd->j++] = cmd->input[cmd->i++];
	}
	cmd->spaced[cmd->j] = '\0';
	printf("DEBUG spaced: [%s]\n", cmd->spaced);
	//return (cmd->spaced);
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
