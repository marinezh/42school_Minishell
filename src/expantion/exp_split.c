#include "minishell.h"

// Creates a list of tokens from split words
static t_token *create_token_list_from_split(char **split)
{
	t_token *head = NULL;
	t_token *last = NULL;
	int i = 0;

	while (split[i])
	{
		t_token *new = malloc(sizeof(t_token)); //checked
		if (!new)
		{
			printf("minishell: memory allocation failed\n"); 
			return NULL;
		}
		new->value = ft_strdup(split[i]);
		new->type = WORD;
		new->next = NULL;
		if (!head)
			head = new;
		else
			last->next = new;
		last = new;
		i++;
	}
	return head;
}

// Checks if token should be split
static int should_split_token(t_token *token)
{
	if (!token)
		return (0);
		
	// Only split WORD or FILE_NAME tokens that contain spaces
	if ((token->type == WORD || token->type == FILE_NAME) && 
		ft_strchr(token->value, ' '))
		return (1);
		
	return (0);
}

// Connects new tokens into the existing token list
// static void connect_new_tokens(t_token **tokens, t_token *prev, 
// 							 t_token *new_tokens, t_token *next, t_token *current)
// {
// 	// Find end of new token list
// 	t_token *last = new_tokens;
// 	while (last && last->next)
// 		last = last->next;

// 	// Connect new tokens to the rest of the list
// 	if (last)
// 		last->next = next;

// 	// Link previous token to start of new list
// 	if (prev)
// 		prev->next = new_tokens;
// 	else
// 		*tokens = new_tokens;  // Update head if needed

// 	// Free the original token
// 	free(current->value);
// 	free(current);
// }

// // Process single token for splitting
// static t_token *process_splittable_token(t_token **tokens, t_token *current, 
// 										t_token *prev, t_token *next)
// {
// 	char **split = quote_safe_split(current->value);
// 	if (!split)
// 		return (next);
// 	if (!split[0]) // Empty result
// 	{
// 		free_split_input(split);
// 		return (next);
// 	}
// 	// Create new tokens with the same type as the original
// 	t_token *new_tokens = create_token_list_from_split(split);
// 	if(!new_tokens)
// 		return NULL;
// 	free_split_input(split);  // Free split array after use
// 	if (!new_tokens)
// 		return (next);
// 	connect_new_tokens(tokens, prev, new_tokens, next, current);
// 	// Find the last token before next
// 	t_token *last_new = new_tokens;
// 	while (last_new && last_new->next && last_new->next != next)
// 		last_new = last_new->next;
// 	return last_new; // Return the last new token
// }
static void connect_new_tokens(t_token_connection *conn)
{
    // Find end of new token list
    t_token *last = conn->new_tokens;
    while (last && last->next)
        last = last->next;

    // Connect new tokens to the rest of the list
    if (last)
        last->next = conn->next;

    // Link previous token to start of new list
    if (conn->prev)
        conn->prev->next = conn->new_tokens;
    else
        *(conn->tokens_head) = conn->new_tokens;  // Update head if needed

    // Free the original token
    free(conn->current->value);
    free(conn->current);
}

// Process single token for splitting (simplified with structure)
static t_token *process_splittable_token(t_token **tokens, t_token *current, 
                                       t_token *prev, t_token *next)
{
    t_token_connection conn;
    char **split;
    t_token *last_new;
    
    split = quote_safe_split(current->value);
    if (!split || !split[0]) // No split or empty result
    {
        if (split)
            free_split_input(split);
        return next;
    }
    
    // Create new tokens with the same type as the original
    conn.new_tokens = create_token_list_from_split(split);
    free_split_input(split);  // Free split array after use
    if (!conn.new_tokens)
        return (NULL);
    
    // Set up the connection parameters
    conn.tokens_head = tokens;
    conn.prev = prev;
    conn.next = next;
    conn.current = current;
    
    // Connect the tokens
    connect_new_tokens(&conn);
    
    // Find the last token before next
    last_new = conn.new_tokens;
    while (last_new && last_new->next && last_new->next != next)
        last_new = last_new->next;
        
    return last_new; // Return the last new token
}

// Main function that handles word splitting
t_token *handle_word_splitting(t_token *tokens, t_data *data)
{
	t_token *current = tokens;
	t_token *prev = NULL;

	while (current != NULL)
	{
		t_token *next = current->next;

		if (should_split_token(current))
		{
			t_token *last_processed = process_splittable_token(&tokens, current, prev, next);
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
			// Move to the next token normally
			prev = current;
			current = next;
		}
	}
	return tokens;
}




					// DEBUG PRINT: Show what was split
					//printf("Split and replaced token with: ");
					// for (t_token *t = new_tokens; t && t != next; t = t->next)
					// 	printf("[%s] ", t->value);
					// printf("\n");