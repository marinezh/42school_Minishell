#include "minishell.h"

void	print_command_debug(t_command *cmd)
{
	int i = 0;

	printf("====== COMMAND ======\n");

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

	// if (cmd->heredoc)
	// 	printf("Heredoc: %s (type: %d)\n", cmd->heredoc, cmd->heredoc_type);

	// if (cmd->logic_op == LOGIC_AND)
	// 	printf("Logic op: &&\n");
	// else if (cmd->logic_op == LOGIC_OR)
	// 	printf("Logic op: ||\n");

	printf("=====================\n");
}

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

t_command	*parse_tokens(char **tokens)
{
	t_command	*head = init_command();
	t_command	*current = head;
	int			i = 0;
	int 		j = 0;
	int			count;

	while (tokens[i])
	{
		if (strcmp(tokens[i], "|") == 0)
		{
			current->pipe = 1;
			current->next = init_command();
			current = current->next; // add if current->next  == NULL
			i++;
		}
		else if (strcmp(tokens[i], "<") == 0)
		{
			i++;
			current->infile = ft_strdup(tokens[i++]);
		}
		else if (strcmp(tokens[i], ">") == 0 || strcmp(tokens[i], ">>") == 0)
		{
			current->append = strcmp(tokens[i], ">>") == 0;
			i++;
			current->outfile = ft_strdup(tokens[i++]);
		}
		else
		{
			// Add token to args list
			count = 0;
			while (current->args && current->args[count])
				count++;
			char **new_args = malloc(sizeof(char *) * (count + 2));
			j = 0;
			while(j < count)
			{
				new_args[j] = current->args[j];
				j++;
			}
			new_args[count] = ft_strdup(tokens[i++]);
			new_args[count + 1] = NULL;
			free(current->args);
			current->args = new_args;
		}
	}
	return (head);
}
