#include "minishell.h"

//////////////////////////////////////////////////////////////////////
// // FOR DEBUGGING, DELETE
// void	print_command_debug(t_command *cmd)
// {
// 	int	i;

// 	i = 0;
// 	printf("====== COMMAND ======\n");
// 	printf("index is %d\n", cmd->index);
// 	if (cmd->args)
// 	{
// 		printf("Args: ");
// 		while (cmd->args[i])
// 		{
// 			printf("'%s' ", cmd->args[i]);
// 			i++;
// 		}
// 		printf("\n");
// 	}
// 	if (cmd->infile)
// 		printf("Infile: %s\n", cmd->infile);
// 	if (cmd->outfile)
// 		printf("Outfile: %s (append: %d)\n", cmd->outfile, cmd->append);
// 	if (cmd->pipe)
// 		printf("Pipe to next: yes\n");
// 	printf("=====================\n");
// }
///////////////////////////////////////////////////////////////////////

// static t_command	*init_command(void)
// {
// 	t_command	*cmd;

// 	cmd = malloc(sizeof(t_command));
// 	if (!cmd)
// 		return (NULL);
// 	cmd->args = NULL;
// 	cmd->index = 0;
// 	cmd->tokens = NULL;
// 	cmd->next = NULL;
// 	return (cmd);
// }

// t_command *parse_tokens(t_token *tokens)
// {
// 	t_command *head;
// 	t_command *current;
// 	int index;
// 	t_token *new_token;
// 	t_token *temp;

// 	head = init_command();
// 	if (!head)
// 	{
// 		fprintf(stderr, "Error: failed to allocate memory for command\n");
// 		return NULL;
// 	}
// 	current = head;
// 	index = 0;
// 	current->index = index++;

// 	while (tokens != NULL)
// 	{
// 		// Handle pipe: start a new command
// 		if (tokens->type == PIPE)
// 		{
// 			current->next = init_command();
// 			if (!current->next)
// 			{
// 				fprintf(stderr, "Error: failed to allocate memory for new command\n");
// 				return NULL;
// 			}
// 			current = current->next;
// 			current->index = index++;
// 		}
// 		// Handle redirections: need to copy both redirection type and its target
// 		else if (tokens->type == REDIR_IN || tokens->type == REDIR_OUT ||
// 		         tokens->type == REDIR_APPEND || tokens->type == HEREDOC)
// 		{
// 			// Copy redirection operator token
// 			new_token = malloc(sizeof(t_token));
// 			if (!new_token)
// 			{
// 				fprintf(stderr, "Error: failed to allocate memory for redirection token\n");
// 				return NULL;
// 			}
// 			new_token->type = tokens->type;
// 			new_token->value = strdup(tokens->value);
// 			if (!new_token->value)
// 			{
// 				free(new_token);
// 				fprintf(stderr, "Error: failed to allocate memory for redirection value\n");
// 				return NULL;
// 			}
// 			new_token->next = NULL;

// 			// Append to current command's token list
// 			if (!current->tokens)
// 				current->tokens = new_token;
// 			else
// 			{
// 				temp = current->tokens;
// 				while (temp->next)
// 					temp = temp->next;
// 				temp->next = new_token;
// 			}

// 			// Move to next token: the file/limiter name
// 			if (tokens->next)
// 			{
// 				tokens = tokens->next;

// 				new_token = malloc(sizeof(t_token));
// 				if (!new_token)
// 				{
// 					fprintf(stderr, "Error: failed to allocate memory for target token\n");
// 					return NULL;
// 				}
// 				new_token->type = tokens->type;
// 				new_token->value = strdup(tokens->value);
// 				if (!new_token->value)
// 				{
// 					free(new_token);
// 					fprintf(stderr, "Error: failed to allocate memory for target value\n");
// 					return NULL;
// 				}
// 				new_token->next = NULL;

// 				// Append to current command's token list
// 				temp = current->tokens;
// 				while (temp->next)
// 					temp = temp->next;
// 				temp->next = new_token;
// 			}
// 		}
// 		else
// 		{
// 			// Regular token: command or argument
// 			new_token = malloc(sizeof(t_token));
// 			if (!new_token)
// 			{
// 				fprintf(stderr, "Error: failed to allocate memory for token\n");
// 				return NULL;
// 			}
// 			new_token->type = tokens->type;
// 			new_token->value = strdup(tokens->value);
// 			if (!new_token->value)
// 			{
// 				free(new_token);
// 				fprintf(stderr, "Error: failed to allocate memory for token value\n");
// 				return NULL;
// 			}
// 			new_token->next = NULL;

// 			// Append to current command's token list
// 			if (!current->tokens)
// 				current->tokens = new_token;
// 			else
// 			{
// 				temp = current->tokens;
// 				while (temp->next)
// 					temp = temp->next;
// 				temp->next = new_token;
// 			}
// 		}

// 		tokens = tokens->next; // advance in input token stream
// 	}

// 	return head;
// }



// t_command	*parse_tokens(t_token *tokens)
// {
// 	t_command	*head;
// 	t_command	*current;
// 	int			count;
// 	int			index;
// 	char		**new_args;
// 	int			j;

// 	head = init_command();
// 	if (!head)
// 	{
// 		fprintf(stderr, "Error: failed to allocate memory for command\n");
// 		return (NULL);
// 	}
// 	current = head;
// 	index = 0;
// 	current->index = index++; // post-increment
// 	while (tokens != NULL)
// 	{
// 		// Pipe handling
// 		if (tokens->type == PIPE)
// 		{
// 			current->pipe = 1;
// 			current->next = init_command();
// 			// Create a new command for the next token
// 			current = current->next;  // Move to the new command
// 			current->index = index++; // post-increment
// 		}
// 		// Input red-n handling
// 		else if (tokens->type == REDIR_IN)
// 		{
// 			tokens = tokens->next; // Move to the next token (the file name)
// 			current->infile = ft_strdup(tokens->value);
// 		}
// 		// Output red-n handling (>) and append redirection (>>)
// 		else if (tokens->type == REDIR_OUT || tokens->type == REDIR_APPEND)
// 		{
// 			current->append = (tokens->type == REDIR_APPEND);
// 			// Set append if it's ">>"
// 			tokens = tokens->next;
// 			// Move to the next token (the file name)
// 			current->outfile = ft_strdup(tokens->value);
// 		}
// 		else
// 		{
// 			// Add token to args list
// 			count = 0;
// 			while (current->args && current->args[count])
// 				count++;
// 			new_args = malloc(sizeof(char *) * (count + 2));
// 			j = 0;
// 			while (j < count)
// 			{
// 				new_args[j] = current->args[j];
// 				j++;
// 			}
// 			new_args[count] = ft_strdup(tokens->value);
// 			// Add the current token's value
// 			new_args[count + 1] = NULL;
// 			free(current->args);      // Free the old args array
// 			current->args = new_args; // Set the new args array
// 		}
// 		tokens = tokens->next; // Move to the next token in the linked list
// 	}
// 	return (head);
// }


