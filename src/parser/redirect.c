#include "minishell.h"

t_files *initialize_file_node(void)
{
	t_files *new_file;
	
	new_file = malloc(sizeof(t_files));
	if (!new_file)
		return (NULL);
	
	new_file->type = -1;
	new_file->fd = -1;
	new_file->next = NULL;
	new_file->to_expand = 0; // default: no expansion
	new_file->name = NULL;
	
	return (new_file);
}

char *extract_unquoted_name(char *name)
{
	char *unquoted_name;
	int len;
	
	len = ft_strlen(name);
	if (len >= 2 && ((name[0] == '\'' && name[len - 1] == '\'') ||
					 (name[0] == '"' && name[len - 1] == '"')))
	{
		unquoted_name = ft_substr(name, 1, len - 2);
		return (unquoted_name);
	}
	return (ft_strdup(name));
}

int  setup_heredoc_node(t_files *new_file, char *name)
{
	int len;
	char *node_name;
	
	len = ft_strlen(name);
	if (len >= 2 && ((name[0] == '\'' && name[len - 1] == '\'') ||
					 (name[0] == '"' && name[len - 1] == '"')))
	{
		node_name = ft_substr(name, 1, len - 2);
		if (!node_name)
			return (0);
		new_file->name = node_name;
		new_file->to_expand = 0;
	}
	else
	{
		new_file->name = ft_strdup(name);
		if (!new_file->name)
			return (0);
		new_file->to_expand = 1;
	}
	return (1);
}

int setup_regular_node(t_files *new_file, char *name)
{
	new_file->name = ft_strdup(name);
	if (!new_file->name)
		return (0);
	new_file->to_expand = 0;  // default: no expansion for normal files
	return (1);
}

t_files *create_file_node(char *name, int type)
{
	t_files *new_file;
	
	new_file = initialize_file_node();
	if (!new_file)
		return (NULL);
	if (type == HEREDOC)
	{
		if (!setup_heredoc_node(new_file, name))
		{
			free(new_file);
			return (NULL);
		}
	}
	else
	{
		if (!setup_regular_node(new_file, name))
		{
			free(new_file);
			return (NULL);
		}
	}
	new_file->type = type;
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
	if (!typed_redir_node)
	{
		free(global_redir_node->name);
		free(global_redir_node);
		return;
	}
	if (type == REDIR_IN || type == HEREDOC)
		append_to_list(&(cmd->in), typed_redir_node);
	else 
		append_to_list(&(cmd->out), typed_redir_node);
}
