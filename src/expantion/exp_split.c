#include "minishell.h"

static t_token	*create_token_list_from_split(char **split)
{
	t_token	*head;
	t_token	*last;
	int		i;

	head = NULL;
	last = NULL;
	i = 0;
	while (split[i])
	{
		t_token *new = malloc(sizeof(t_token)); // checked
		if (!new)
		{
			printf("minishell: memory allocation failed\n");
			return (NULL);
		}
		new->value = ft_strdup(split[i]); // checked
		if (!new->value)
		{
			printf("minishell: memory allocation failed\n");
			free(new);
			return (NULL);
		}
		new->type = WORD;
		new->next = NULL;
		if (!head)
			head = new;
		else
			last->next = new;
		last = new;
		i++;
	}
	return (head);
}

// Checks if token should be split
static int	should_split_token(t_token *token)
{
	if (!token)
		return (0);
	// Only split WORD or FILE_NAME tokens that contain spaces
	if ((token->type == WORD || token->type == FILE_NAME)
		&& ft_strchr(token->value, ' '))
	{
		return (1);
	}
	return (0);
}

static void	connect_new_tokens(t_token_connection *conn)
{
	t_token	*last;

	// Find end of new token list
	last = conn->new_tokens;
	while (last && last->next)
		last = last->next;
	// Connect new tokens to the rest of the list
	if (last)
		last->next = conn->next;
	// Link previous token to start of new list
	if (conn->prev)
		conn->prev->next = conn->new_tokens;
	else
		*(conn->tokens_head) = conn->new_tokens; // Update head if needed
	// Free the original token
	free(conn->current->value);
	free(conn->current);
}

// Process single token for splitting (simplified with structure)
static t_token	*process_spl_tok(t_token **tokens, t_token *current,
		t_token *prev, t_token *next)
{
	t_token_connection	conn;
	char				**split;
	t_token				*last_new;

	split = quote_safe_split(current->value); // checked
	if (!split || !split[0])                  // No split or empty result
	{
		if (split)
			free_split_input(split);
		printf("minishell: memory allocation failed\n");
		return (NULL);
	}
	conn.new_tokens = create_token_list_from_split(split); // checked
	free_split_input(split);
	if (!conn.new_tokens)
		return (printf("minishell: memory allocation failed\n"), NULL);
	conn.tokens_head = tokens; // Set up the connection parameters
	conn.prev = prev;
	conn.next = next;
	conn.current = current;
	connect_new_tokens(&conn);  // Connect the tokens
	last_new = conn.new_tokens; // Find the last token before next
	while (last_new && last_new->next && last_new->next != next)
		last_new = last_new->next;
	return (last_new); // Return the last new token
}

int	handle_word_splitting(t_token **tokens, t_data *data)
{
	t_token	*current;
	t_token	*prev;
	t_token	*next;

	current = *tokens;
	prev = NULL;
	while (current != NULL)
	{
		next = current->next;
		if (should_split_token(current))
		{
			t_token *last_processed = process_spl_tok(tokens, current, prev,
					next); // checked
			if (!last_processed)
			{
				data->status = ERR_GENERIC;
				return (-1);
			}
			prev = last_processed;
			current = next;
		}
		else
		{
			prev = current; // Move to the next token normally
			current = next;
		}
	}
	return (0);
}
