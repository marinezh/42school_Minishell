#include "minishell.h"

// Creates a list of tokens from split words
static t_token *create_token_list_from_split(char **split)
{
	t_token *head = NULL;
	t_token *last = NULL;
	int i = 0;

	while (split[i])
	{
		t_token *new = NULL; //malloc(sizeof(t_token)); //checked
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
static void connect_new_tokens(t_token **tokens, t_token *prev, 
							 t_token *new_tokens, t_token *next, t_token *current)
{
	// Find end of new token list
	t_token *last = new_tokens;
	while (last && last->next)
		last = last->next;

	// Connect new tokens to the rest of the list
	if (last)
		last->next = next;

	// Link previous token to start of new list
	if (prev)
		prev->next = new_tokens;
	else
		*tokens = new_tokens;  // Update head if needed

	// Free the original token
	free(current->value);
	free(current);
}

// Process single token for splitting
static t_token *process_splittable_token(t_token **tokens, t_token *current, 
										t_token *prev, t_token *next)
{
	char **split = quote_safe_split(current->value);
	if (!split)
		return (next);
	if (!split[0]) // Empty result
	{
		free_split_input(split);
		return (next);
	}
	// Create new tokens with the same type as the original
	t_token *new_tokens = create_token_list_from_split(split);
	if(!new_tokens)
		return NULL;
	free_split_input(split);  // Free split array after use
	if (!new_tokens)
		return (next);
	connect_new_tokens(tokens, prev, new_tokens, next, current);
	// Find the last token before next
	t_token *last_new = new_tokens;
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

// t_token *handle_word_splitting(t_token *tokens)
// {
// 	t_token *current = tokens;
// 	t_token *prev = NULL;

// 	while (current != NULL)
// 	{
// 		t_token *next = current->next;

// 		if ((current->type == WORD || current->type == FILE_NAME) && // Only split WORD or FILE_NAME tokens that contain spaces
// 			ft_strchr(current->value, ' '))
// 		{
// 			//printf("XXX there is a space found in token: [%s]\n", current->value);
// 			char **split = quote_safe_split(current->value);
// 			if (!split)
// 			{
// 				prev = current;
// 				current = next; // If splitting failed, skip to next token
// 				continue;
// 			}
// 			if (split[0]) // Only proceed if we got at least one word
// 			{
// 				// Create new tokens with the same type as the original
// 				t_token *new_tokens = create_token_list_from_split(split);
// 				free_split_input(split);  // Free split array after use

// 				if (new_tokens)
// 				{
// 					// Find end of new token list
// 					t_token *last = new_tokens;
// 					while (last && last->next)
// 						last = last->next;

// 					// Connect new tokens to the rest of the list
// 					if (last)
// 						last->next = next;

// 					// Link previous token to start of new list
// 					if (prev)
// 						prev->next = new_tokens;
// 					else
// 						tokens = new_tokens;  // Update head if needed

// 					// Free the original token
// 					free(current->value);
// 					free(current);

// 					// Move current and prev to the last of the new tokens
// 					current = new_tokens;
// 					while (current && current->next && current->next != next)
// 						current = current->next;
// 					prev = current;
// 					current = next;
// 					continue;
// 				}
// 			}
// 			else
// 			{
// 				free_split_input(split);  // Free empty split result
// 			}
// 		}
// 		// Move to the next token normally
// 		prev = current;
// 		current = next;
// 	}
// 	return tokens;
// }


					// DEBUG PRINT: Show what was split
					//printf("Split and replaced token with: ");
					// for (t_token *t = new_tokens; t && t != next; t = t->next)
					// 	printf("[%s] ", t->value);
					// printf("\n");