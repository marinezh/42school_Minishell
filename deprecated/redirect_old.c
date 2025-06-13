// void	add_redirection(t_command *cmd, char *filename, int type)
// {
// 	t_files	*new_file;
// 	t_files *redir_node;
// 	t_files	**target_list = NULL;
// 	t_files	**redir_list = NULL;
// 	t_files	*current;

// 	// Sanity check
// 	if (!cmd || !filename)
// 		return;
// 	// Set redir_list for all types
// 	if (type == REDIR_IN || type == HEREDOC || type == REDIR_OUT || type == REDIR_APPEND)
// 	{
// 		redir_list = &(cmd->redirections);
// 		redir_node = create_file_node(filename, type);
// 		if (!redir_node)
// 			return;

// 		if (*redir_list == NULL)
// 			*redir_list = redir_node;
// 		else
// 		{
// 			current = *redir_list;
// 			while (current->next)
// 				current = current->next;
// 			current->next = redir_node;
// 		}
// 	}
// 	else
// 		return; // Invalid type — log error or return silently
	
// 	// Assign target list
// 	if (type == REDIR_IN || type == HEREDOC)
// 		target_list = &(cmd->in);
// 	else if (type == REDIR_OUT || type == REDIR_APPEND)
// 		target_list = &(cmd->out);

// 	if (!target_list)
// 		return;

// 	new_file = create_file_node(filename, type);
// 	if (!new_file)
// 		return;

// 	if (*target_list == NULL)
// 		*target_list = new_file;
// 	else
// 	{
// 		current = *target_list;
// 		while (current->next)
// 			current = current->next;
// 		current->next = new_file;
// 	}
// }