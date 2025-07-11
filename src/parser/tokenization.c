#include "minishell.h"

t_token	*create_token_node(char *value)
{
	t_token	*token;
	(void)value;
	token = malloc(sizeof(t_token)); // Checked 
	if (!token)
		return (NULL);
	token->value = ft_strdup(value); // Checked
	if (!token->value)
	{
		free(token);
		return (NULL);
	}
	token->next = NULL;
	token->prev = NULL;
	token->type = NONE;
	token->in_db_quotes = 0;
	return (token);
}

void	append_token(t_token **head, t_token **tail, t_token *new_token)
{
	if (!*head)
		*head = new_token;
	else
	{
		(*tail)->next = new_token;
		new_token->prev = *tail;
	}
	*tail = new_token;
}

int	determine_token_type(t_token *token, char *value)
{
	if (ft_strcmp(value, "|") == 0)
		token->type = PIPE;
	else if (ft_strcmp(value, "<") == 0)
		token->type = REDIR_IN;
	else if (ft_strcmp(value, "<<") == 0)
		token->type = HEREDOC;
	else if (ft_strcmp(value, ">") == 0)
		token->type = REDIR_OUT;
	else if (ft_strcmp(value, ">>") == 0)
		token->type = REDIR_APPEND;
	else
		token->type = WORD;
	return (1);
}

void	update_file_name_tokens(t_token *head)
{
	t_token	*current;

	current = head;
	while (current && current->next)
	{
		if ((current->type == REDIR_IN || current->type == REDIR_OUT
				|| current->type == REDIR_APPEND || current->type == HEREDOC)
			&& current->next->type == WORD)
		{
			current->next->type = FILE_NAME;
		}
		current = current->next;
	}
}

t_token	*tokenize_input(char **split_input, t_data *data)
{
	t_token	*head;
	t_token	*tail;
	t_token	*new_token;
	int		i;

	head = NULL;
	tail = NULL;
	i = 0;
	while (split_input[i])
	{
		new_token = create_token_node(split_input[i]); // CHECKED
		if (!new_token)
		{
			printf("minishell: memory allocation failed\n");
			data->status = ERR_GENERIC;
			return (NULL);
		}
		determine_token_type(new_token, split_input[i]);
		append_token(&head, &tail, new_token);
		i++;
	}
	update_file_name_tokens(head);
	return (head);
}
