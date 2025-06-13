#include "minishell.h"

// void free_tokens(char **tokens)
// {
// 	int i = 0;

// 	if (!tokens)
// 		return ;
// 	while (tokens[i])
// 	{
// 		free(tokens[i]);
// 	}
// 	free(tokens);
// }
void	free_tokens(t_token *tokens)
{
	t_token	*tmp;

	while (tokens != NULL)
	{
		tmp = tokens;
		tokens = tokens->next;
		free(tmp->value); // Free the value
		free(tmp);        // Free the token itself
	}
}

void	free_file_list(t_files *files)
{
	t_files	*tmp;

	while (files)
	{
		tmp = files;
		files = files->next;
		if (tmp->name)
			free(tmp->name);
		if (tmp->fd >= 0)
			close(tmp->fd);
		free(tmp);
	}
}
void	free_command_list(t_command *commands)
{
	t_command	*tmp;
	int			i;

	while (commands)
	{
		tmp = commands; // we use tmp pointer as we free node by node
		commands = commands->next;
		// Free args (array of strings)
		if (tmp->args)
		{
			i = 0;
			while (tmp->args[i])
				free(tmp->args[i++]);
			free(tmp->args);
		}
		free_file_list(tmp->in);
		free_file_list(tmp->out);
		free(tmp); // Free the command itself
	}
}

void	free_split_input(char **split)
{
	int	i;

	i = 0;
	if (!split)
		return ;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}
void free_split_result(char **result, int i)
{
	int k;

	k = 0;
	while (k < i)
	{
		if(result[k])
			free(result[k]);
		k++;
	}
	free(result);
}
