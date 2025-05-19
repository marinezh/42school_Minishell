// #include "minishell.h"

// t_files	*create_file_node(char *name, int type)
// {
// 	t_files	*new_file;

// 	new_file = malloc(sizeof(t_files));
// 	if (!new_file)
// 		return (NULL);
// 	new_file->name = NULL;
// 	if (name)
// 		new_file->name = ft_strdup(name);
// 	new_file->type = type;
// 	new_file->fd = -1;
// 	new_file->next = NULL;
// 	return (new_file);
// }

// void	append_file(t_files **head, t_files *new_node)
// {
// 	t_files	*current;

// 	// t_files *new_node = malloc(sizeof(t_files));
// 	if (!new_node)
// 		return ;
// 	if (!*head)
// 	{
// 		*head = new_node;
// 		return ;
// 	}
// 	current = *head;
// 	while (current->next)
// 		current = current->next;
// 	current->next = new_node;
// }
// t_files	*parse_redir(t_token *token_list)
// {
// 	t_files	*head;
// 	char	*file_name;
// 	int		redir_type;
// 	t_files	*node;

// 	head = NULL;
// 	// t_files *tail = NULL;
// 	// t_files *current = NULL;
// 	while (token_list)
// 	{
// 		if ((token_list->type == REDIR_OUT || token_list->type == REDIR_APPEND
// 				|| token_list->type == REDIR_IN || token_list->type == HEREDOC)
// 			&& token_list->next && token_list->next->type == WORD)
// 		{
// 			file_name = token_list->next->value;
// 			redir_type = token_list->type;
// 			node = create_file_node(file_name, redir_type);
// 			append_file(&head, node);
// 			token_list = token_list->next; // skip filename token
// 		}
// 		token_list = token_list->next;
// 	}
// 	return (head);
// }

// // Utility: Free a t_files structure's name (safe cleanup)
// void	free_file(t_files *file)
// {
// 	if (file && file->name)
// 		free(file->name);
// 	file->name = NULL;
// 	file->type = NONE;
// 	file->fd = -1;
// 	file->next = NULL;
// }

// // Utility: Set a t_files structure
// void	set_file(t_files *file, const char *name, t_token_type type)
// {
// 	if (file->name)
// 		free(file->name);
// 	file->name = strdup(name); // strdup allocates new memory
// 	file->type = type;
// 	file->fd = -1; // Default invalid fd
// 	file->next = NULL;
// }

// // Core function: Extract last input and output redirections from token list
// void	extract_redirections(t_command *cmd)
// {
// 	t_token	*token;

// 	token = cmd->tokens;
// 	// Clear existing redirection names/types
// 	free_file(&cmd->in);
// 	free_file(&cmd->out);
// 	while (token)
// 	{
// 		if ((token->type == REDIR_IN || token->type == HEREDOC
// 				|| token->type == REDIR_OUT || token->type == REDIR_APPEND)
// 			&& token->next && token->next->type == WORD)
// 		{
// 			if (token->type == REDIR_IN || token->type == HEREDOC)
// 			{
// 				set_file(&cmd->in, token->next->value, token->type);
// 			}
// 			else if (token->type == REDIR_OUT || token->type == REDIR_APPEND)
// 			{
// 				set_file(&cmd->out, token->next->value, token->type);
// 			}
// 			token = token->next; // skip filename
// 		}
// 		token = token->next;
// 	}
// }
