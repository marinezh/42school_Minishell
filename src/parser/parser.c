#include "minishell.h"

//////////////////////////////////////////////////////////////////////
//FOR DEBUGGING, DELETE
void	print_command_debug(t_command *cmd)
{
	int i = 0;

	printf("====== COMMAND ======\n");
	printf("index is %d\n", cmd->index);
	if (cmd->args)
	{
		printf("Args: ");
		while (cmd->args[i])
		{
			printf("'%s' ", cmd->args[i]);
			i++;
		}
		printf("\n");
	}
	if (cmd->infile)
		printf("Infile: %s\n", cmd->infile);
	if (cmd->outfile)
		printf("Outfile: %s (append: %d)\n", cmd->outfile, cmd->append);
	if (cmd->pipe)
		printf("Pipe to next: yes\n");
	printf("=====================\n");
}
///////////////////////////////////////////////////////////////////////


static t_command	*init_command(void)
{
	t_command *cmd = malloc(sizeof(t_command));
	if (!cmd)
		return (NULL);
	cmd->args = NULL;
	cmd->infile = NULL;
	cmd->outfile = NULL;
	cmd->append = 0;
	cmd->pipe = 0;
	cmd->next = NULL;
	return (cmd);
}

t_command *parse_tokens(t_token *tokens)
{
	t_command *head = init_command();
	t_command *current = head;
	int count;
	int index = 0;

	current->index = index++; // post-increment
	while (tokens != NULL)
	{
		// Pipe handling
		if (tokens->type == PIPE)
		{
			current->pipe = 1;
			current->next = init_command();  // Create a new command for the next token
			current = current->next;  // Move to the new command
			current->index = index++; // post-increment
		}
		// Input red-n handling
		else if (tokens->type == REDIR_IN)
		{
			tokens = tokens->next;  // Move to the next token (the file name)
			current->infile = ft_strdup(tokens->value);
		}
		// Output red-n handling (>) and append redirection (>>)
		else if (tokens->type == REDIR_OUT || tokens->type == REDIR_APPEND)
		{
			current->append = (tokens->type == REDIR_APPEND);  // Set append if it's ">>"
			tokens = tokens->next;  // Move to the next token (the file name)
			current->outfile = ft_strdup(tokens->value);
		}
		else
		{
			// Add token to args list
			count = 0;
			while (current->args && current->args[count])
				count++;

			char **new_args = malloc(sizeof(char *) * (count + 2));
			int j = 0;
			while (j < count)
			{
				new_args[j] = current->args[j];
				j++;
			}
			new_args[count] = ft_strdup(tokens->value);  // Add the current token's value
			new_args[count + 1] = NULL;

			free(current->args);  // Free the old args array
			current->args = new_args;  // Set the new args array
		}

		tokens = tokens->next;  // Move to the next token in the linked list
	}
	return head;
}

