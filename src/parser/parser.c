/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhivoto <mzhivoto@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 00:38:43 by mzhivoto          #+#    #+#             */
/*   Updated: 2025/07/15 00:56:43 by mzhivoto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static t_command	*create_new_command(int index)
{
	t_command	*cmd;

	cmd = malloc(sizeof(t_command));
	if (!cmd)
		return (NULL);
	cmd->index = index;
	cmd->args = NULL;
	cmd->redirections = NULL;
	cmd->in = NULL;
	cmd->out = NULL;
	cmd->pipe = 0;
	cmd->next = NULL;
	return (cmd);
}

static t_command	*add_cmd_to_chain(t_command **head, t_command **tail,
		int *cmd_index)
{
	t_command	*current;

	current = create_new_command((*cmd_index)++);
	if (!current)
		return (NULL);
	if (!(*head))
		*head = current;
	if (*tail)
		(*tail)->next = current;
	*tail = current;
	return (current);
}

static int	process_tok(t_command **cur, t_token **tok_list, t_cmd_chain *chain)
{
	if (!tok_list)
		return (0);
	if (!(*cur))
	{
		*cur = add_cmd_to_chain(&chain->head, &chain->tail, &chain->cmd_index);
		if (!(*cur))
			return (0);
	}
	if ((*tok_list)->type == PIPE)
		handle_pipe(*cur, tok_list, cur);
	else if (is_redirect_type(*tok_list))
	{
		if (!handle_redirection(*cur, tok_list))
			return (0);
	}
	else if ((*tok_list)->type == WORD)
	{
		if (!handle_word_token(*cur, tok_list))
			return (0);
	}
	else
		*tok_list = (*tok_list)->next;
	return (1);
}

t_command	*parse_tokens(t_token *token_list, t_data *data)
{
	t_cmd_chain	chain;
	t_command	*current;

	chain.head = NULL;
	chain.tail = NULL;
	current = NULL;
	chain.cmd_index = 0;
	while (token_list)
	{
		if (!process_tok(&current, &token_list, &chain))
		{
			free_command_list(chain.head);
			printf("minishell: memory allocation failed\n");
			data->status = ERR_GENERIC;
			return (NULL);
		}
	}
	return (chain.head);
}

t_command	*parse_input(t_command *commands, t_data *data, char *input)
{
	char	**split_input;
	t_token	*tokens;

	split_input = preprocess_input(input, data);
	if (!split_input)
		return (NULL);
	tokens = tokenize_input(split_input, data);
	free_split_input(split_input);
	if (!tokens)
		return (NULL);
	if (error_check(tokens, data))
		return (free_tokens(tokens), NULL);
	if (expand_variables(tokens, data) == -1)
		return (free_tokens(tokens), NULL);
	if (handle_word_splitting(&tokens, data) == -1)
		return (free_tokens(tokens), NULL);
	delete_empty_tokens(&tokens);
	commands = parse_tokens(tokens, data);
	if (!commands)
		return (free_tokens(tokens), NULL);
	if (remove_quotes_from_command_args(commands, data) == -1)
		return (free_tokens(tokens), free_command_list(commands), NULL);
	free_tokens(tokens);
	return (commands);
}
