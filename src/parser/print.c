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
void	print_command_debug(t_command *cmd)
{
	t_token	*current_token;

	printf("====== COMMAND ======\n");
	printf("index is %d\n", cmd->index);
	if (cmd->tokens)
	{
		printf("Tokens: ");
		current_token = cmd->tokens;
		while (current_token)
		{
			printf("'%s' ", current_token->value);
			current_token = current_token->next;
		}
		printf("\n");
	}
	if (cmd->next)
		printf("Pipe to next command: yes\n");
	printf("=====================\n");
}
