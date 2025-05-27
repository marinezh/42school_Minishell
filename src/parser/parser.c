#include <minishell.h>

t_command	*create_new_command(int index)
{
	t_command	*cmd;

	cmd = malloc(sizeof(t_command));
	if (!cmd)
		return (NULL);
	cmd->index = index;
	cmd->args = NULL;
	cmd->in = NULL;
	cmd->out = NULL;
	cmd->pipe = 0;
	cmd->next = NULL;
	return (cmd);
}

// t_files	*create_file_node(char *name, int type)
// {
// 	t_files	*new_file;

// 	new_file = malloc(sizeof(t_files));
// 	if (!new_file)
// 		return (NULL);
// 	new_file->name = ft_strdup(name);
// 	if (!new_file->name)
// 	{
// 		free(new_file);
// 		return (NULL);
// 	}
// 	new_file->type = type;
// 	new_file->fd = -1;
// 	new_file->next = NULL;
// 	return (new_file);
// }

// void	add_redirection(t_command *cmd, char *filename, int type)
// {
// 	t_files	*new_file;
// 	t_files	**list;
// 	t_files	*current;

// 	if (type == REDIR_IN || type == HEREDOC) // IN
// 		list = &(cmd->in);
// 	else // REDIR_OUT or REDIR_APPEND
// 		list = &(cmd->out);
// 	new_file = create_file_node(filename, type);
// 	if (!new_file)
// 		return ; // Handle error in the calling function
// 	if (*list == NULL)
// 		*list = new_file;
// 	else
// 	{
// 		current = *list;
// 		while (current->next)
// 			current = current->next;
// 		current->next = new_file;
// 	}
// }

// char	**realloc_args(char **args, int count, char *value)
// {
// 	int		i;
// 	char	**new_args;

// 	i = 0;
// 	new_args = malloc(sizeof(char *) * (count + 2));
// 	if (!new_args)
// 		return (NULL);
// 	while (i < count)
// 	{
// 		new_args[i] = args[i];
// 		i++;
// 	}
// 	new_args[count] = ft_strdup(value);
// 	new_args[count + 1] = NULL;
// 	if (args)
// 		free(args);
// 	return (new_args);
// }

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

// void handle_pipe(t_command *current, t_token **token_list,
// 					t_command **current_cmd)
// {
// 	current->pipe = 1;
// 	*current_cmd = NULL;
// 	*token_list = (*token_list)->next;
// }
// int handle_redirection(t_command *current, t_token **token_list)
// {
// 	int redir_type;
	
// 	redir_type = (*token_list)->type;
// 	*token_list = (*token_list)->next;
	
// 	if (*token_list && ((*token_list)->type == WORD || (*token_list)->type == FILE_NAME))
// 	{
// 		add_redirection(current, (*token_list)->value, redir_type);
// 		*token_list = (*token_list)->next;
// 		return (1);
// 	}
// 	return (0);
// }

// int handle_word_token(t_command *current, t_token **token_list)
// {
// 	int argc;
	
// 	argc = 0;
// 	while (current->args && current->args[argc])
// 		argc++;
// 	current->args = realloc_args(current->args, argc, (*token_list)->value);
// 	if (!current->args)
// 		return (0);
// 	*token_list = (*token_list)->next;
// 	return (1);
// }

int process_token(t_command **current, t_token **token_list,
		t_command **head, t_command **tail, int *cmd_index)
{
	if (!(*current)) // Create a new command if needed
	{
		*current = add_command_to_chain(head, tail, cmd_index);
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
