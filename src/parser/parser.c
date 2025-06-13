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
	//cmd->pipe = 0;
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



int process_token(t_command **current, t_token **token_list,
		t_command **head, t_command **tail, int *cmd_index)
{
	if (!(*current)) // Create a new command if needed
	{
		*current = add_command_to_chain(head, tail, cmd_index);
		if (!(*current))
			return (0);
	}
	// if ((*token_list)->type == PIPE)
	// {
	// 	handle_pipe(*current, token_list, current);
	// }
	if ((*token_list)->type == REDIR_IN || (*token_list)->type == HEREDOC ||
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
	t_command *head;
	t_command *tail;
	t_command *current;
	int command_index;

	head = NULL;
	tail = NULL;
	current = NULL;
	command_index = 0;
	
	while (token_list)
	{
		if (!process_token(&current, &token_list, &head, &tail, &command_index))
		{
			free_command_list(head);
			return (NULL);
		}
	}
	return (head);
}
