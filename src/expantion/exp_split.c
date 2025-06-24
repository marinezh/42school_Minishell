#include "minishell.h"

// t_token *handle_word_splitting(t_token *tokens)
// {
//     // Initialize pointers for list traversal
//     t_token *current = tokens;   // Current token being examined
//     t_token *prev = NULL;        // Previous token in the list
    
//     // Process all tokens in the list
//     while (current != NULL)
//     {
//         // Save the next token before potential modifications to avoid losing it
//         t_token *next = current->next;
        
//         // Only split WORD or FILE_NAME tokens that contain spaces
//         if ((current->type == WORD || current->type == FILE_NAME) && 
//             ft_strchr(current->value, ' '))
//         {
//             // Debug output
//             print_tokens(tokens);
//             printf("XXX there is a space found XXX\n");
            
//             // Split the token value by spaces, preserving quoted sections
//             char **split = quote_safe_split(current->value, ' ');
            
//             // Only proceed if split was successful and returned at least one part
//             if (split && split[0])
//             {
//                 // Convert the split array to a linked list of tokens
//                 t_token *new_tokens = create_token_list_from_split(split, current->type);
//                 free_split_input(split);  // Free the array after creating tokens
                
//                 // Only proceed if we successfully created new tokens
//                 if (new_tokens)
//                 {
//                     // Find the end of the new token list to connect with the remainder
//                     t_token *last = new_tokens;
//                     while (last->next)
//                         last = last->next;
                    
//                     // Connect the end of new tokens to the remainder of the original list
//                     last->next = next;
                    
//                     // Update the list connections - either connect to previous token
//                     // or update the head of the list if we're at the first token
//                     if (prev)
//                         prev->next = new_tokens;
//                     else
//                         tokens = new_tokens;  // Update the head pointer
                    
//                     // Clean up the original token that was split
//                     free(current->value);
//                     free(current);
                    
//                     // Update current pointer to the first token of the new list
//                     current = new_tokens;
//                 }
//             }
            
//             // Debug output showing result after splitting
//             print_tokens(tokens);
//         }
        
//         // Move to the next token in the list
//         prev = current;
//         current = next;
//     }
    
//     return tokens;  // Return possibly modified tokens list head
// }
// t_token *handle_word_splitting(t_token *tokens)
// {
//     t_token *current = tokens;
//     t_token *prev = NULL;
    
//     while (current != NULL)
//     {
//         t_token *next = current->next;
        
//         // Only split WORD or FILE_NAME tokens that contain spaces
//         if ((current->type == WORD || current->type == FILE_NAME) && 
//             ft_strchr(current->value, ' '))
//         {
//             printf("XXX there is a space found XXX\n");
            
//             // Split the token value by spaces
//             char **split = quote_safe_split(current->value, ' ');
//             if (!split)
//                 continue;  // Skip this token if splitting failed
            
//             // Only proceed if we got at least one word
//             if (split[0])
//             {
//                 // Create new tokens with the same type as the original
//                 t_token *new_tokens = create_token_list_from_split(split, current->type);
//                 free_split_input(split);  // Free split array after use
                
//                 if (new_tokens)
//                 {
//                     // Find end of new token list
//                     t_token *last = new_tokens;
//                     while (last && last->next)
//                         last = last->next;
                    
//                     // Connect new tokens to the rest of the list
//                     if (last)
//                         last->next = next;
                        
//                     // Link previous token to start of new list
//                     if (prev)
//                         prev->next = new_tokens;
//                     else
//                         tokens = new_tokens;  // Update head if needed
                    
//                     // Clean up the original token
//                     free(current->value);
//                     free(current);
                    
//                     // Move current to the first of the new tokens
//                     current = new_tokens;
//                 }
//             }
//             else
//             {
//                 free_split_input(split);  // Free empty split result
//             }
//         }
        
//         // Move to the next token
//         prev = current;
//         current = next;
//     }
    
//     return tokens;
// }
// void replace_current_with_multiple(t_token **current, t_token *new_tokens)
// {
// 	if (!current || !*current || !new_tokens)
// 		return;

// 	t_token *old = *current;
// 	t_token *tail = new_tokens;

// 	// Find the last token in the new list
// 	while (tail->next)
// 		tail = tail->next;

// 	// Link rest of old list after new tokens
// 	tail->next = old->next;

// 	// Replace current token pointer with new list head
// 	*current = new_tokens;

// 	// Free the original token
// 	free(old->value);
// 	free(old);
// }

static t_token *create_token_list_from_split(char **split)
{
	t_token *head = NULL;
	t_token *last = NULL;
	int i = 0;

	while (split[i])
	{
		t_token *new = malloc(sizeof(t_token));
		if (!new)
			return NULL;
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

t_token *handle_word_splitting(t_token *tokens)
{
	t_token *current = tokens;
	t_token *prev = NULL;

	while (current != NULL)
	{
		t_token *next = current->next;

		// Only split WORD or FILE_NAME tokens that contain spaces
		if ((current->type == WORD || current->type == FILE_NAME) && 
			ft_strchr(current->value, ' '))
		{
			//printf("XXX there is a space found in token: [%s]\n", current->value);

			// Split the token value by spaces
			char **split = quote_safe_split(current->value, ' ');
			if (!split)
			{
				// If splitting failed, skip to next token
				prev = current;
				current = next;
				continue;
			}

			// Only proceed if we got at least one word
			if (split[0])
			{
				// Create new tokens with the same type as the original
				//t_token *new_tokens = create_token_list_from_split(split, current->type);
				t_token *new_tokens = create_token_list_from_split(split);
				free_split_input(split);  // Free split array after use

				if (new_tokens)
				{
					// DEBUG PRINT: Show what was split
					//printf("Split and replaced token with: ");
					// for (t_token *t = new_tokens; t && t != next; t = t->next)
					// 	printf("[%s] ", t->value);
					// printf("\n");

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
						tokens = new_tokens;  // Update head if needed

					// Free the original token
					free(current->value);
					free(current);

					// Move current and prev to the last of the new tokens
					current = new_tokens;
					while (current && current->next && current->next != next)
						current = current->next;
					prev = current;
					current = next;
					continue;
				}
			}
			else
			{
				free_split_input(split);  // Free empty split result
			}
		}

		// Move to the next token normally
		prev = current;
		current = next;
	}

	return tokens;
}
