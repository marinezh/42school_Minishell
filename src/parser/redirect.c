#include "minishell.h"

t_files	*create_file_node(char *name, int type)
{
	t_files	*new_file;
	int len;

	//printf("DEBUG create_file_node: Creating node type %d for name '%s'\n", type, name);
	new_file = malloc(sizeof(t_files));
	if (!new_file)
		return (NULL);

	if (type == HEREDOC)
	{
		len = ft_strlen(name);
		printf("DEBUG: Checking heredoc delimiter '%s', length %d\n", name, len);
		if (len >= 2 &&
 				((name[0] == '\'' && name[len - 1] == '\'') ||
    			(name[0] == '"' && name[len - 1] == '"')))

		{
			printf("DEBUG: Found single quotes in heredoc delimiter\n");
			char *unquoted_name = ft_substr(name, 1, len - 2);
			if (!unquoted_name)
			{
				free(new_file);
				return (NULL);
			}
			new_file->name = unquoted_name;
			new_file->to_expand = 0;
			printf("DEBUG: Quoted heredoc delimiter: '%s', to_expand=0\n", new_file->name);
		}
		else
		{
			new_file->name = ft_strdup(name);
			if (!new_file->name)
			{
				free(new_file);
				return (NULL);
			}
			new_file->to_expand = 1;
			printf("DEBUG: Unquoted heredoc delimiter: '%s', to_expand=1\n", new_file->name);
		}
	}
	else
	{
		new_file->name = ft_strdup(name);
		if (!new_file->name)
		{
			free(new_file);
			return (NULL);
		}
		new_file->to_expand = 0;  // default: no expansion for normal files
	}

	new_file->type = type;
	new_file->fd = -1;
	new_file->next = NULL;
	//printf("DEBUG: Created file node with name '%s', expand_vars=%d\n", 
           //new_file->name, new_file->to_expand);
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
