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

char **preprocess_input(char *input)
{
	t_cmd_input cmd = {0};
	char **split_input = NULL;
	cmd.input = input;
	if (!input)						// if set to NULL seg fault, do i need this extra check here?
	{
		printf("Input is NULL.\n");
		return NULL;
	}
	add_space(&cmd);
	if (!cmd.spaced)
	{
		printf("Failed to add spacing to input.\n");
		return (NULL);
	}
	//printf("new input: %s\n", cmd.spaced);
	split_input = quote_safe_split(cmd.spaced, ' ');
	if (!split_input)
	{
		printf("Splitting input failed.\n");
		return (NULL);
	}
	// FOR DEBUGGIN , delete later
	// for (int j = 0; split_input[j]; j++)
	// printf("token[%d] = [%s]\n", j, split_input[j]);
	free(cmd.spaced);
	return split_input;
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
