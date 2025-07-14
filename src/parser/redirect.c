#include "minishell.h"

static t_files	*initialize_file_node(void)
{
	t_files	*new_file;

	new_file = malloc(sizeof(t_files)); // CHECKED
	if (!new_file)
		return (NULL);
	new_file->type = -1;
	new_file->fd = -1;
	new_file->next = NULL;
	new_file->to_expand = 0; // default: no expansion
	new_file->name = NULL;
	return (new_file);
}

static int	setup_heredoc_node(t_files *new_file, char *name)
{
	int		len;
	char	*node_name;

	len = ft_strlen(name);
	if (len >= 2 && ((name[0] == '\'' && name[len - 1] == '\'')
			|| (name[0] == '"' && name[len - 1] == '"')))
	{
		node_name = ft_substr(name, 1, len - 2); // CHECKED
		if (!node_name)
			return (0);
		new_file->name = node_name;
		new_file->to_expand = 0;
	}
	else
	{
		new_file->name = ft_strdup(name); // Checked
		if (!new_file->name)
			return (0);
		new_file->to_expand = 1;
	}
	return (1);
}

static int	setup_regular_node(t_files *new_file, char *name)
{
	new_file->name = ft_strdup(name); // checked
	if (!new_file->name)
		return (0);
	new_file->to_expand = 0;
	return (1);
}

static t_files	*create_file_node(char *name, int type)
{
	t_files	*new_file;

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

int	add_redirection(t_command *cmd, char *filename, int type)
{
	t_files	*global_redir_node;
	t_files	*typed_redir_node;

	if (!cmd || !filename)
		return (0);
	global_redir_node = create_file_node(filename, type); // checked
	if (!global_redir_node)
	{
		return (0);
	}
	append_to_list(&(cmd->redirections), global_redir_node);
	typed_redir_node = create_file_node(filename, type); // checked
	if (!typed_redir_node)
		return (0);
	if (type == REDIR_IN || type == HEREDOC)
		append_to_list(&(cmd->in), typed_redir_node);
	else
		append_to_list(&(cmd->out), typed_redir_node);
	return (1);
}
