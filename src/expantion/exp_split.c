#include "minishell.h"

static t_token	*create_token_list_from_split(char **split)
{
	t_splitted_tok	tok;
	int				i;

	tok.head = NULL;
	tok.last = NULL;
	i = 0;
	while (split[i])
	{
		tok.new = malloc(sizeof(t_token)); // checked
		if (!tok.new)
			return (printf("minishell: memory allocation failed\n"), NULL);
		tok.new->value = ft_strdup(split[i]); // checked
		if (!tok.new->value)
			return (printf("minishell: memory error\n"), free(tok.new), NULL);
		tok.new->type = WORD;
		tok.new->next = NULL;
		if (!tok.head)
			tok.head = tok.new;
		else
			tok.last->next = tok.new;
		tok.last = tok.new;
		i++;
	}
	return (tok.head);
}

static int	should_split_token(t_token *token)
{
	if (!token)
		return (0);
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

	last = conn->new_tokens;
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

// Process single token for splitting (simplified with structure)
static t_token	*pr_spl_tok(t_token **tok, t_token *cur,t_token *prev, t_token *next)
{
	t_token_connection	conn;
	char				**split;
	t_token				*last_new;

	split = quote_safe_split(cur->value); // checked
	if (!split || !split[0])
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
	conn.tokens_head = tok;
	conn.prev = prev;
	conn.next = next;
	conn.current = cur;
	connect_new_tokens(&conn);
	last_new = conn.new_tokens;
	while (last_new && last_new->next && last_new->next != next)
		last_new = last_new->next;
	return (last_new);
}

int	handle_word_splitting(t_token **tokens, t_data *data)
{
	t_splitted_word	word;

	word.cur = *tokens;
	word.prev = NULL;
	while (word.cur != NULL)
	{
		word.next = word.cur->next;
		if (should_split_token(word.cur))
		{
			word.last = pr_spl_tok(tokens, word.cur, word.prev,word.next); // checked
			if (!word.last)
			{
				data->status = ERR_GENERIC;
				return (-1);
			}
			word.prev = word.last;
			word.cur = word.next;
		}
		else
		{
			word.prev = word.cur;
			word.cur = word.next;
		}
	}
	return (0);
}
