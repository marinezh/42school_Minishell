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

	while (tokens)
	{
		tmp = tokens->next;
		if (tokens->value)
			free(tokens->value);
		free(tokens);
		tokens = tmp;
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
		free_file_list(tmp->redirections);
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
/**
 * Frees multiple string pointers
 * Function accepts a variable number of string pointers and frees each one
 * The last argument must be NULL to indicate the end of arguments
 */
void free_strings(char *str, ...)
{
	va_list args;
	char *ptr;

	if (str)
		free(str);

	va_start(args, str);
	while ((ptr = va_arg(args, char *)) != NULL)
		free(ptr);

	va_end(args);
}
void	free_exp_parts(t_exp_parts *parts)
{
	if (!parts)
		return;
	free(parts->status_str);
	free(parts->prefix);
	free(parts->suffix);
	free(parts->new_value);
	free(parts->final_value);
	*parts = (t_exp_parts){0}; // resets all to NULL
}