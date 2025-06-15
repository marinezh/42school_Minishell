#include "minishell.h"

int	read_prompt(t_cmd_input *cmd)
{
	sig_received = 0;
	cmd->input = readline("minishell$ ");
	if (sig_received)
	{
		if (cmd->input)
		{
			free(cmd->input);
			cmd->input = NULL;
		}
		return (0);
	}
	if (!cmd->input)
	{
		printf("exit\n");
		return (-1);
	}
	if (cmd->input[0] == '\0')
	{
		free(cmd->input);
		cmd->input = NULL;
		return (0);
	}
	return (1);
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
