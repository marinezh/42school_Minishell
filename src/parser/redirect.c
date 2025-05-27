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