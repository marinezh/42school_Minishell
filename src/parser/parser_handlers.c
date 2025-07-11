#include "minishell.h"

char	**realloc_args(char **args, int count, char *value)
{
	int		i;
	char	**new_args;

	i = 0;
	new_args = malloc(sizeof(char *) * (count + 2)); // checked
	if (!new_args)
		return (NULL);
	while (i < count)
	{
		new_args[i] = args[i];
		i++;
	}
	new_args[count] = ft_strdup(value);
	new_args[count + 1] = NULL;
	if (args)
		free(args);
	return (new_args);
}

void	handle_pipe(t_command *current, t_token **token_list,
		t_command **current_cmd)
{
	current->pipe = 1;
	*current_cmd = NULL;
	*token_list = (*token_list)->next;
}

int	handle_redirection(t_command *current, t_token **token_list)
{
	int	redir_type;

	redir_type = (*token_list)->type;
	*token_list = (*token_list)->next;
	if (*token_list && ((*token_list)->type == WORD
			|| (*token_list)->type == FILE_NAME))
	{
		if (!add_redirection(current, (*token_list)->value, redir_type))
		{
			return 0;
		}
		*token_list = (*token_list)->next;
		return (1);
	}
	return (1);
}

int	handle_word_token(t_command *current, t_token **token_list)
{
	int	argc;

	argc = 0;
	while (current->args && current->args[argc])
		argc++;
	current->args = realloc_args(current->args, argc, (*token_list)->value); //Checked
	if (!current->args)
		return (0);
	*token_list = (*token_list)->next;
	return (1);
}
