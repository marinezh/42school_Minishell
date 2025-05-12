#include "minishell.h"

// void free_tokens(char **tokens)
// {
// 	int i = 0;

// 	if (!tokens)
// 		return;
// 	while (tokens[i])
// 	{
// 		free(tokens[i]);
// 	}
// 	free(tokens);
// }
void free_tokens(t_token *tokens)
{
	t_token *tmp;
	while (tokens != NULL) {
		tmp = tokens;
		tokens = tokens->next;
		free(tmp->value);		// Free the value
		free(tmp);				// Free the token itself
	}
}
void free_command_list(t_command *commands)
{
	t_command *tmp;
	int i;
	while (commands)
	{
		tmp = commands;
		commands = commands->next;

		// Free args (array of strings)
		if (tmp->args)
		{
			i = 0;
			while (tmp->args[i])
				free(tmp->args[i++]);
			free(tmp->args);
		}
		// Free tokens using your existing function
		if (tmp->tokens)
			free_tokens(tmp->tokens);
		free(tmp); // Free the command itself
	}
}