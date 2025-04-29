#include "minishell.h"

// int count_tokens(char **split_input)
// {
// 	int count = 0;
// 	while (split_input[count] != NULL)
// 		count++;
// 	return count;
// }

t_token *tokenize_input(char *input)
{
    char **split_input = quote_safe_split(input, ' ');  // Ensure this splits safely around quotes
    //nt token_count = count_tokens(split_input);
    t_token *head = NULL, *tail = NULL;  // Keep track of the head and tail of the linked list
    int i = 0;

    while (split_input[i]) {
        t_token *new_token = malloc(sizeof(t_token));  // Allocate memory for a new token
        if (!new_token) {
            printf("Memory allocation failed for a new token.\n");
            return NULL;
        }

        // Check the type of the token and assign accordingly
        if (strcmp(split_input[i], "|") == 0) {
            new_token->type = PIPE;
        } else if (strcmp(split_input[i], "<") == 0) {
            new_token->type = REDIR_IN;
        } else if (strcmp(split_input[i], ">") == 0) {
            new_token->type = REDIR_OUT;
        } else if (strcmp(split_input[i], ">>") == 0) {
            new_token->type = REDIR_APPEND;
        } else if (strcmp(split_input[i], "<<") == 0) {
            new_token->type = HEREDOC;
        } else {
            new_token->type = WORD;  // Default case for regular words
        }

        new_token->value = strdup(split_input[i]);  // Save the token value
        if (!new_token->value) {
            printf("Memory allocation failed for token value.\n");
            return NULL;
        }
        new_token->next = NULL;  // Initialize the next pointer to NULL

        // Add the new token to the linked list
        if (head == NULL) {
            head = new_token;  // The first token is the head
            tail = head;       // Tail points to the head initially
        } else {
            tail->next = new_token;  // Link the current token to the next
            tail = new_token;        // Move the tail to the new token
        }
        i++;
    }

    return head;  // Return the head of the linked list
}
void print_tokens(t_token *tokens)
{
    while (tokens != NULL) {
        switch (tokens->type) {
            case WORD:
                printf("WORD: %s\n", tokens->value);
                break;
            case PIPE:
                printf("PIPE: %s\n", tokens->value);
                break;
            case REDIR_IN:
                printf("REDIR_IN: %s\n", tokens->value);
                break;
            case REDIR_OUT:
                printf("REDIR_OUT: %s\n", tokens->value);
                break;
            case REDIR_APPEND:
                printf("REDIR_APPEND: %s\n", tokens->value);
                break;
            case HEREDOC:
                printf("HEREDOC: %s\n", tokens->value);
                break;
            default:
                printf("Unknown token type\n");
                break;
        }
        tokens = tokens->next;  // Move to the next token in the linked list
    }
}

