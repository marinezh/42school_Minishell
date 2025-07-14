#include "minishell.h"
// Frees a token list used on error
static void free_token_list_on_error(t_token *head)
{
	t_token *tmp;
	while (head)
	{
		tmp = head->next;
		free(head->value);
		free(head);
		head = tmp;
	}
}

// Creates a list of tokens from split strings
static t_token *create_token_list_from_split(char **split)
{
	t_token *head = NULL;
	t_token *last = NULL;
	int i = 0;

	while (split[i])
	{
		t_token *new = malloc(sizeof(t_token));
		if (!new)
		{
			printf("minishell: memory allocation failed\n");
			free_token_list_on_error(head);
			return NULL;
		}
		new->value = ft_strdup(split[i]);
		if (!new->value)
		{
			printf("minishell: memory allocation failed\n");
			free(new);
			free_token_list_on_error(head);
			return NULL;
		}
		new->type = WORD;
		new->next = NULL;
		new->prev = NULL;
		if (!head)
			head = new;
		else
			last->next = new;
		last = new;
		i++;
	}
	return head;
}

// Determines whether a token should be split
static int should_split_token(t_token *token)
{
	if (!token)
		return 0;
	if ((token->type == WORD || token->type == FILE_NAME) &&
		ft_strchr(token->value, ' '))
	{
		printf("SHOULD SPLIT\n");
		return 1;
	}
	return 0;
}

// Connects a newly split token list into the full token list
static void connect_new_tokens(t_token_connection *conn)
{
	t_token *last = conn->new_tokens;
	while (last && last->next)
		last = last->next;

	if (last)
		last->next = conn->next;
	if (conn->prev)
		conn->prev->next = conn->new_tokens;
	else
		*(conn->tokens_head) = conn->new_tokens;

	free(conn->current->value);
	free(conn->current);
}

// Splits a token and connects the resulting list into the original token stream
static t_token *process_spl_tok(t_token **tokens, t_token *current, t_token *prev, t_token *next)
{
	t_token_connection conn;
	char **split = quote_safe_split(current->value);
	if (!split || !split[0])
	{
		free_split_input(split);
		return next;
	}

	conn.new_tokens = create_token_list_from_split(split);
	free_split_input(split);
	if (!conn.new_tokens)
		return NULL;

	conn.tokens_head = tokens;
	conn.prev = prev;
	conn.next = next;
	conn.current = current;
	connect_new_tokens(&conn);

	t_token *last_new = conn.new_tokens;
	while (last_new && last_new->next && last_new->next != next)
		last_new = last_new->next;

	return last_new;
}

// Performs word splitting on a token list
t_token *handle_word_splitting(t_token *tokens, t_data *data)
{
	t_token *current = tokens;
	t_token *prev = NULL;

	while (current)
	{
		t_token *next = current->next;

		if (should_split_token(current))
		{
			t_token *last_processed = process_spl_tok(&tokens, current, prev, next);
			if (!last_processed)
			{
				data->status = ERR_GENERIC;
				return NULL;
			}
			prev = last_processed;
			current = next;
		}
		else
		{
			prev = current;
			current = next;
		}
	}
	return tokens;
}
