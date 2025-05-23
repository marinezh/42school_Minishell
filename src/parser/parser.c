#include <minishell.h>

t_command	*create_new_command(int index)
{
	t_command	*cmd;

	cmd = malloc(sizeof(t_command));
	if (!cmd)
		return (NULL);
	cmd->index = index;
	cmd->args = NULL;
	cmd->in = NULL;  // input redirection list
	cmd->out = NULL; // output redirection list
	cmd->pipe = 0;   // Not a pipe by default
	cmd->next = NULL;
	return (cmd);
}

// Helper function to create a new redirection file node
t_files	*create_file_node(char *name, int type)
{
	t_files	*new_file;

	new_file = malloc(sizeof(t_files));
	if (!new_file)
		return (NULL);
	new_file->name = ft_strdup(name);
	if (!new_file->name)
	{
		free(new_file);
		return (NULL);
	}
	new_file->type = type;
	new_file->fd = -1; // Initialize fd to -1 (unopened)
	new_file->next = NULL;
	return (new_file);
}
// Helper function to add a redirection to the linkedlist
void	add_redirection(t_command *cmd, char *filename, int type)
{
	t_files	*new_file;
	t_files	**list;
	t_files	*current;

	if (type == REDIR_IN || type == HEREDOC) // IN
		list = &(cmd->in);
	else // REDIR_OUT or REDIR_APPEND
		list = &(cmd->out);
	new_file = create_file_node(filename, type);
	if (!new_file)
		return ; // Handle error in the calling function
	// Add to the end of the appropriate list
	if (*list == NULL)
		*list = new_file;
	else
	{
		current = *list;
		while (current->next)
			current = current->next;
		current->next = new_file;
	}
}

char	**realloc_args(char **args, int count, char *value)
{
	int		i;
	char	**new_args;

	i = 0;
	new_args = malloc(sizeof(char *) * (count + 2));
	if (!new_args)
		return (NULL);
	while (i < count)
	{
		new_args[i] = args[i];
		i++;
	}
	new_args[count] = ft_strdup(value);
	new_args[count + 1] = NULL;
	if (args)
		free(args);
	return (new_args);
}


t_command	*parse_tokens(t_token *token_list)
{
	t_command	*head;
	t_command	*tail;
	t_command	*current;
	int			command_index;
	int			argc;
	int			redir_type;

	head = NULL;
	tail = NULL;
	current = NULL;
	command_index = 0;
	while (token_list)
	{
		if (!current) // On PIPE or at start, create a new command
		{
			current = create_new_command(command_index++);
			if (!head)
				head = current;
			if (tail)
				tail->next = current;
			tail = current;
		}
		if (token_list->type == PIPE)
		{
			current->pipe = 1;
			current = NULL;
			token_list = token_list->next;
			continue ;
		}
		
		// Handle redirections
		if (token_list->type == REDIR_IN || token_list->type == HEREDOC
			|| token_list->type == REDIR_OUT
			|| token_list->type == REDIR_APPEND)
		{
			redir_type = token_list->type;
			token_list = token_list->next;
			// Check if next token exists and is a valid filename
			if (token_list && (token_list->type == WORD
					|| token_list->type == FILE_NAME))
			{
				add_redirection(current, token_list->value, redir_type);
				token_list = token_list->next;
			}
			// Do i need extra error handling here for missing filename after redirection ?
			else
			{
				continue ; // think about error hendling here
			}
		}
		// Add WORD tokens to args
		else if (token_list->type == WORD)
		{
			argc = 0;
			while (current->args && current->args[argc])
				argc++;
			current->args = realloc_args(current->args, argc,token_list->value);
			token_list = token_list->next;
		}
		else
		{
			// Handle other token types
			token_list = token_list->next;
		}
	}
	return (head);
}
