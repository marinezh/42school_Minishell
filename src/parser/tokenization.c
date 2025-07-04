#include "minishell.h"

t_token	*create_token_node(char *value)
{
	t_token	*token;
	//printf("initial value %s\n", value);
	token = malloc(sizeof(t_token));
	if (!token)
	{
		printf("memory allocation failed\n");
		return (NULL);
	}
	token->value = ft_strdup(value);
	if (!token->value)
	{
		printf("memory allocation failed\n");
		free(token);
		return (NULL);
	}
	token->next = NULL;
	token->prev = NULL;
	token->type = NONE;
	token->in_db_quotes = 0;
	
	return (token);
}
// t_token	*create_token_node(char *value)
// {
// 	t_token	*token = malloc(sizeof(t_token));
// 	if (!token)
// 		return (NULL);

// 	token->value = ft_strdup(value);
// 	if (!token->value)
// 	{
// 		free(token);
// 		return (NULL);
// 	}

// 	size_t len = ft_strlen(token->value);
// 	token->in_db_quotes = 0;

// 	if (len >= 2 && ((token->value[0] == '"' && token->value[len - 1] == '"') ||
// 	                 (token->value[0] == '\'' && token->value[len - 1] == '\'')))
// 	{
// 		token->in_db_quotes = (token->value[0] == '"');
// 		// remove outer quotes
// 		char *unquoted = ft_substr(token->value, 1, len - 2);
// 		free(token->value);
// 		token->value = unquoted;
// 	}

// 	// expansion flag: only allow if unquoted or inside double quotes
// 	token->expantion = (ft_strchr(token->value, '$') != NULL);

// 	token->next = NULL;
// 	token->prev = NULL;
// 	token->type = NONE;
// 	token->file = NULL;
// 	printf("[TOKEN CREATE] %s, exp=%d (quoted=%d)\n", value, token->expantion, token->in_db_quotes);

// 	return token;
// }
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

int	determine_token_type(t_token *token, char *value, int *pending_redirection)
{
	if (ft_strcmp(value, "|") == 0)
	{
		token->type = PIPE;
		*pending_redirection = 0;
	}
	else if (ft_strcmp(value, "<") == 0)
	{
		token->type = REDIR_IN;
		*pending_redirection = 1;
	}
	else if (ft_strcmp(value, "<<") == 0)
	{
		token->type = HEREDOC;
		*pending_redirection = 1;
	}
	else if (ft_strcmp(value, ">") == 0)
	{
		token->type = REDIR_OUT;
		*pending_redirection = 1;
	}
	else if (ft_strcmp(value, ">>") == 0)
	{
		token->type = REDIR_APPEND;
		*pending_redirection = 1;
	}
	else if (*pending_redirection)
	{
		token->type = FILE_NAME;
		*pending_redirection = 0;
	}
	else
		token->type = WORD;
	return (1);
}


t_token	*tokenize_input(char **split_input)
{
	t_token		*head;
	t_token		*tail;
	t_token		*new_token;
	int pending_redirection;
	int i;

	head = NULL;
	tail = NULL;
	i = 0;
	pending_redirection = 0; // Flag to assign FILE_NAME to next token
	while (split_input[i])
	{
		new_token = create_token_node(split_input[i]);
		if (!new_token)
		{
			printf("Memory allocation failed for a new token.\n");
			return (NULL);
		}
		determine_token_type(new_token, split_input[i], &pending_redirection);
		append_token(&head, &tail, new_token);
		i++;
	}
	// for (int i = 0; split_input[i]; i++)
    // 	free(split_input[i]);
	// free(split_input);
	return (head);
}
