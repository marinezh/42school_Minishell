#include "minishell.h"

// t_token *tokenize_input(char *input)
// {
// 	t_cmd_input cmd = {0};
// 	cmd.input = input;

// 	//char *spaced_input = add_space(&cmd);
// 	add_space(&cmd);
// 	if (!cmd.spaced) {
// 		printf("Failed to add spacing to input.\n");
// 		return NULL;
// 	}
// 	printf("new input: %s\n", cmd.spaced);
// 	char **split_input = quote_safe_split(cmd.spaced, ' ');
// 	if (!split_input) 
// 	{
// 		printf("Splitting input failed.\n");
// 		return NULL;
// 	}
// 	t_token *head = NULL;
// 	t_token *tail = NULL;  // track of the head and tail of the linked list
// 	int i = 0;

// 	while (split_input[i])
// 	{
// 		t_token *new_token = malloc(sizeof(t_token));
// 		if (!new_token)
// 		{
// 			printf("Memory allocation failed for a new token.\n");
// 			return NULL;
// 		}
// 		if (ft_strcmp(split_input[i], "|") == 0) 
// 			new_token->type = PIPE;
// 		else if (ft_strcmp(split_input[i], "<") == 0) 
// 			new_token->type = REDIR_IN;
// 		else if (ft_strcmp(split_input[i], ">") == 0) 
// 			new_token->type = REDIR_OUT;
// 		else if (ft_strcmp(split_input[i], ">>") == 0) 
// 			new_token->type = REDIR_APPEND;
// 		else if (ft_strcmp(split_input[i], "<<") == 0) 
// 			new_token->type = HEREDOC;
// 		else 
// 			new_token->type = WORD;  // Default case for regular words

// 		new_token->value = ft_strdup(split_input[i]);  // Save the token value
// 		if (!new_token->value) {
// 			printf("Memory allocation failed for token value.\n");
// 			return NULL;
// 		}
// 		new_token->next = NULL;  // Initialize the next pointer to NULL
// 		new_token->prev = tail;  //its prev points to the current tail;
// 		// Add the new token to the linked list
// 		if (head == NULL) 
// 		{
// 			head = new_token;  // The first token is the head
// 			tail = head;       // Tail points to the head initially
// 		} else 
// 		{
// 			tail->next = new_token;  // Link the current token to the next
// 			tail = new_token;        // Move the tail to the new token
// 		}
// 		i++;
// 	}
// 	return head;  // Return the head of the linked list
// }


t_token *tokenize_input(char *input)
{
	t_cmd_input cmd = {0};
	cmd.input = input;

	add_space(&cmd);
	if (!cmd.spaced) {
		printf("Failed to add spacing to input.\n");
		return NULL;
	}
	printf("new input: %s\n", cmd.spaced);

	char **split_input = quote_safe_split(cmd.spaced, ' ');
	if (!split_input) {
		printf("Splitting input failed.\n");
		return NULL;
	}

	t_token *head = NULL;
	t_token *tail = NULL;
	int pending_redirection = 0; // Flag to assign FILE_NAME to next token

	for (int i = 0; split_input[i]; i++) {
		t_token *new_token = malloc(sizeof(t_token));
		if (!new_token) {
			printf("Memory allocation failed for a new token.\n");
			return NULL;
		}

		// ==============================
		// Doubly-linked list construction
		// ==============================

		new_token->next = NULL;
		new_token->prev = tail;

		if (!head)
			head = new_token;
		else
			tail->next = new_token;

		tail = new_token;

		// ==============================

		// Determine token type
		if (ft_strcmp(split_input[i], "|") == 0)
		{
			new_token->type = PIPE;
			pending_redirection = 0;
		}
		else if (ft_strcmp(split_input[i], "<") == 0)
		{
			new_token->type = REDIR_IN;
			pending_redirection = 1;
		}
		else if (ft_strcmp(split_input[i], ">") == 0)
		{
			new_token->type = REDIR_OUT;
			pending_redirection = 1;
		}
		else if (ft_strcmp(split_input[i], ">>") == 0)
		{
			new_token->type = REDIR_APPEND;
			pending_redirection = 1;
		}
		else if (ft_strcmp(split_input[i], "<<") == 0)
		{
			new_token->type = HEREDOC;
			pending_redirection = 1;
		}
		else if (pending_redirection)
		{
			new_token->type = FILE_NAME;
			pending_redirection = 0;
		}
		else
		{
			new_token->type = WORD;
		}

		new_token->value = ft_strdup(split_input[i]);
		if (!new_token->value) {
			printf("Memory allocation failed for token value.\n");
			free(new_token);
			return NULL;
		}
	}

	return head;
}
