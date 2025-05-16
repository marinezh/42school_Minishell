#include "minishell.h"

t_files *create_file_node(char *name, int type)
{
	t_files *new_file= malloc(sizeof(t_files));
	if (!new_file)
		return NULL;
	new_file->name = NULL;
	if(name)
		new_file->name = ft_strdup(name);
	new_file->type = type;
	new_file->fd = -1;
	new_file->next = NULL;
	return new_file;
}

void append_file(t_files **head, t_files *new_node)
{
	//t_files *new_node = malloc(sizeof(t_files));
	if(!new_node)
		return ;
	if(!*head)
	{
		*head = new_node;
		return ;
	}
	t_files *current = *head;
	while(current->next)
		current = current->next;
	current->next = new_node;
}
t_files *parse_redir(t_token *token_list)
{
	t_files *head = NULL;
	//t_files *tail = NULL;
	//t_files *current = NULL;

	while(token_list)
	{
		if((token_list->type == REDIR_OUT || token_list->type == REDIR_APPEND ||
			token_list->type == REDIR_IN || token_list->type == HEREDOC)
		   && token_list->next && token_list->next->type == WORD)
		{
			char *file_name = token_list->next->value;
			int redir_type = token_list->type;

			t_files *node = create_file_node(file_name, redir_type);
			append_file(&head, node);

			token_list = token_list->next; //skip filename token
		}
		token_list = token_list->next;
	}
	return head;
}

void print_files_nodes(t_files *files)
{
	while(files)
	{
		printf("File name %s, file_type %d\n", files->name, files->type);
		files = files->next;
	}
}