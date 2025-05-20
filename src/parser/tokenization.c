#include "minishell.h"

t_token *create_token_node(char *value)
{
	t_token *token = malloc(sizeof(t_token));
	if (!token)
	{
		printf("memory allocation failed\n");
		return NULL;
	}
	token->value = ft_strdup(value);
	if (!token->value)
	{
		printf("memory allocation failed\n");
		free(token);
		return NULL;
	}
	token->next = NULL;
	token->prev = NULL;
	token->type = NONE;
	return token;
}

void append_token(t_token **head, t_token **tail, t_token *new_token)
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

int determine_toke_type(t_token *token, char *value, int *pending_redirection)
{
	if(ft_strcmp(value, "|") == 0)
	{
		token->type = PIPE;
		*pending_redirection = 0;
	}
	else if(ft_strcmp(value, "<") == 0)
	{
		token->type = REDIR_IN;
		*pending_redirection = 1;
	}
	else if(ft_strcmp(value, "<<") == 0)
	{
		token->type = HEREDOC;
		*pending_redirection = 1;
	}
	else if(ft_strcmp(value, ">") == 0)
	{
		token->type = REDIR_OUT;
		*pending_redirection = 1;
	}
	else if(ft_strcmp(value, ">>") == 0)
	{
		token->type = REDIR_APPEND;
		*pending_redirection = 1;
	}
	else if(*pending_redirection)
	{
		token->type = FILE_NAME;
		*pending_redirection = 0;
	}
	else
		token->type = WORD;
	return 1;
}
