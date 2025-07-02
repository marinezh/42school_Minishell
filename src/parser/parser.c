#include <minishell.h>

t_command	*create_new_command(int index)
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

t_command *add_command_to_chain(t_command **head, t_command **tail, int *cmd_index)
{
	t_command *current;
	
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



int process_token(t_command **current, t_token **token_list, t_cmd_chain *chain)
{
	if (!(*current)) // Create a new command if needed
	{
		*current = add_command_to_chain( &chain->head, &chain->tail, &chain->cmd_index);
		if (!(*current))
			return (0);
	}
	if ((*token_list)->type == PIPE)
	{
		handle_pipe(*current, token_list, current);
	}
	else if ((*token_list)->type == REDIR_IN || (*token_list)->type == HEREDOC ||
			(*token_list)->type == REDIR_OUT || (*token_list)->type == REDIR_APPEND)
	{
		if (!handle_redirection(*current, token_list))
			return (1);  // Skip to next token but don't exit parsing
	}
	else if ((*token_list)->type == WORD)
	{
		if (!handle_word_token(*current, token_list))
			return (0);
	}
	else
		*token_list = (*token_list)->next;
	return (1);
}

t_command *parse_tokens(t_token *token_list)
{

	t_cmd_chain chain;
	t_command *current;
	//int command_index;

	chain.head = NULL;
	chain.tail = NULL;
	current = NULL;
	chain.cmd_index = 0;
	
	while (token_list)
	{
		 ///printf("Processing token: %s of type %d\n", token_list->value, token_list->type);
		if (!process_token(&current, &token_list, &chain))
		{
			//printf("Error processing token, freeing resources\n");
            free_command_list(chain.head);
            free_tokens(token_list);
            return NULL;
		}
	}
	return (chain.head);
}
