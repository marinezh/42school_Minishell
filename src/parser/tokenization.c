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

char **preprocess_input(char *input, t_data *data)
{
	t_cmd_input cmd;
	char *spaced;
	char **split_input;
	
	ft_memset(&cmd, 0, sizeof(t_cmd_input));
	split_input = NULL;
	if (!input || input[0] == '\0')						// if set to NULL seg fault, do i need this extra check here?
	{
		data->status = 127;  // Consider empty input as non-error (or choose 1)
		return NULL;
	}
	cmd.input = input;
	spaced = add_space(&cmd, data);
	if (!spaced)
		return NULL; // error msg comes from add_space
	//printf("new input: %s\n", cmd.spaced);
	split_input = quote_safe_split(spaced, ' ');
	if (!split_input)
	{
		ft_putstr_fd("minishell: splitting input failed QUOTES\n", 2);
		//data->status = 2;
		return (NULL);
	}
	free(spaced);
	// FOR DEBUGGIN , delete later
	for (int j = 0; split_input[j]; j++)
	printf("token[%d] = [%s]\n", j, split_input[j]);
	
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
