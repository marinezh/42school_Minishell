#include "minishell.h"

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
	new_file->fd = -1;
	new_file->next = NULL;
	return (new_file);
}

void append_to_list(t_files **list, t_files *node)
{
	t_files *current;
	
	if (*list == NULL)
	{
		*list = node;
		return;
	}
	current = *list;
	while (current->next)
		current = current->next;
	current->next = node;
}
void add_redirection(t_command *cmd, char *filename, int type)
{
	t_files	*global_redir_node;
	t_files	*typed_redir_node;
	
	if (!cmd || !filename)
		return;
	global_redir_node = create_file_node(filename, type);
	if (!global_redir_node)
		return;
	append_to_list(&(cmd->redirections), global_redir_node);
	typed_redir_node = create_file_node(filename, type);
	{
		free(global_redir_node->name);
		return;
	}
	if (type == REDIR_IN || type == HEREDOC)
		append_to_list(&(cmd->in), typed_redir_node);
	else 
		append_to_list(&(cmd->out), typed_redir_node);
}
