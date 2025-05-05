#include "minishell.h"

// void	print_command_debug(t_command *cmd)
// {
// 	int i;

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

// void	print_command_debug(t_command *cmd)
// {
// 	t_token	*current_token;

// 	printf("====== COMMAND ======\n");
// 	printf("index is %d\n", cmd->index);
// 	if (cmd->tokens)
// 	{
// 		printf("Tokens: ");
// 		current_token = cmd->tokens;
// 		while (current_token)
// 		{
// 			printf("'%s' ", current_token->value);
// 			current_token = current_token->next;
// 		}
// 		printf("\n");
// 	}
// 	// Handle redirection (input and output)
// 	if (cmd->tokens)
// 	{
// 		// Check for redirection
// 		current_token = cmd->tokens;
// 		while (current_token)
// 		{
// 			if (current_token->type == REDIR_IN)
// 				printf("Infile: %s\n",
// 					current_token->next ? current_token->next->value : "NULL");
// 			if (current_token->type == REDIR_OUT
// 				|| current_token->type == REDIR_APPEND)
// 				printf("Outfile: %s (append: %d)\n",
// 					current_token->next ? current_token->next->value : "NULL",
// 					current_token->type == REDIR_APPEND);
// 			current_token = current_token->next;
// 		}
// 	}
// 	if (cmd->pipe)
// 		printf("Pipe to next: yes\n");
// 	printf("=====================\n");
// }
// void	print_command_debug(t_command *cmd)
// {
// 	t_token	*current_token;

// 	printf("====== COMMAND ======\n");
// 	printf("index is %d\n", cmd->index);
// 	if (cmd->tokens)
// 	{
// 		printf("Tokens: ");
// 		current_token = cmd->tokens;
// 		while (current_token)
// 		{
// 			printf("'%s' ", current_token->value);
// 			current_token = current_token->next;
// 		}
// 		printf("\n");
// 	}
// 	if (cmd->next)
// 		printf("Pipe to next command: yes\n");
// 	printf("=====================\n");
// }
void print_command_debug(t_command *cmd)
{
    t_token *current_token;

    printf("====== COMMAND ======\n");
    printf("index is %d\n", cmd->index);

    // Check if there are any tokens in the current command
    if (cmd->tokens)
    {
        printf("Tokens: ");
        current_token = cmd->tokens;

        // Iterate through all tokens in the current command
        while (current_token != NULL)
        {
            // Print the token type and value
            switch (current_token->type)
            {
                case WORD:
                    printf("WORD('%s') ", current_token->value);
                    break;
                case PIPE:
                    printf("PIPE('%s') ", current_token->value);
                    break;
                case REDIR_OUT:
                    printf("REDIR_OUT('%s') ", current_token->value);
                    break;
                case REDIR_APPEND:
                    printf("REDIR_APPEND('%s') ", current_token->value);
                    break;
                case REDIR_IN:
                    printf("REDIR_IN('%s') ", current_token->value);
                    break;
                case HEREDOC:
                    printf("HEREDOC('%s') ", current_token->value);
                    break;
                default:
                    printf("UNKNOWN('%s') ", current_token->value);
                    break;
            }

            current_token = current_token->next;
        }
        printf("\n");
    }

    // Print the next command (if any)
    if (cmd->next)
    {
        printf("Next command exists: yes\n");
    }

    printf("=====================\n");
}