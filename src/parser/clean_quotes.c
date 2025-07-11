#include "minishell.h"

void	remove_outer_quotes_from_string(char *str)
{
	int		i;
	int		j;
	char	*temp;
	char	in_quote;

	i = 0;
	j = 0;
	temp = (char *)malloc(ft_strlen(str) + 1);
	if (!temp)
		return ;
	in_quote = 0;
	while (str[i])
	{
		if ((str[i] == '\'' || str[i] == '"') && !in_quote)
		{
			in_quote = str[i]; 			// Start of quote
			i++;
		}
		else if (str[i] == in_quote)
		{
			in_quote = 0; // End of quote
			i++;
		}
		else
			temp[j++] = str[i++]; // Copy character
	}
	temp[j] = '\0';
	ft_strlcpy(str, temp, ft_strlen(str) + 1); // Copy back to original
	free(temp);
}

void	remove_quotes_from_files(t_files *files)
{
	t_files	*current;

	current = files;
	while (current)
	{
		if (current->type != HEREDOC)
			remove_outer_quotes_from_string(current->name);
		current = current->next;
	}
}

void	remove_quotes_from_command_args(t_command *commands)
{
	t_command	*current;
	int			i;

	current = commands;
	while (current)
	{
		if (current->args)
		{
			i = 0;
			while (current->args[i])
			{
				remove_outer_quotes_from_string(current->args[i]);
				i++;
			}
		}
		if (current->redirections)
			remove_quotes_from_files(current->redirections);
		if (current->in)
			remove_quotes_from_files(current->in);
		if (current->out)
			remove_quotes_from_files(current->out);
		current = current->next;
	}
}
