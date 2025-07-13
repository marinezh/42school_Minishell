#include <minishell.h>

static t_command	*create_new_command(int index)
{
	t_command	*cmd;

	cmd = malloc(sizeof(t_command)); // Checked
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

static int	process_token(t_command **cur, t_token **token_list, t_cmd_chain *chain)
{
	if (!token_list)
		return (0);
	if (!(*cur))
	{
		*cur = add_cmd_to_chain(&chain->head, &chain->tail, &chain->cmd_index); //checked
		if (!(*cur))
			return (0);
	}
	if ((*token_list)->type == PIPE)
		handle_pipe(*cur, token_list, cur);
	else if (is_redirect_type(*token_list))
	{
		if (!handle_redirection(*cur, token_list))
			return (0);
	}
	else if ((*token_list)->type == WORD)
	{
		if (!handle_word_token(*cur, token_list))
			return (0);
	}
	else
		*token_list = (*token_list)->next;
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
		if (!process_token(&current, &token_list, &chain))
		{
			free_command_list(chain.head);
			// free_tokens(token_list);
			printf("minishell: memory allocation failed\n");
			data->status = ERR_GENERIC;
			return (NULL);
		}
	}
	return (chain.head);
}
