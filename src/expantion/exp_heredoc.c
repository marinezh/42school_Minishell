#include "minishell.h"

static int process_token_variables(t_token *token, t_data *data)
{
	int i;

	i = 0;
	while (token->value && token->value[i])
	{
		if (token->value[i] == '$')
		{
			if (token->value[i + 1] == '?')
			{
				if (!process_status_var(token, data, &i))
					return (0);
				continue;
			}
			else if (ft_isalpha(token->value[i + 1]) || token->value[i + 1] == '_')
			{
				if (!process_expantion(token, data, &i))
					return (0);
				continue;
			}
		}
		i++;
	}
	return (1);
}

int expand_heredoc_file(t_token *tokens, t_data *data)
{
	t_token *current;

	if (!tokens || !data)
		return (0);
		
	current = tokens;
	while (current)
	{
		if (!process_token_variables(current, data))
			return (0);
		current = current->next;
	}
	return (1);
}

char *expand_heredoc_line(char *input, t_data *data)
{
	t_token temp;

	temp.value = ft_strdup(input);
	if (!temp.value)
		return (NULL);
	temp.type = WORD;
	temp.next = NULL;
	if (!expand_heredoc_file(&temp, data))
	{
		free(temp.value);
		return NULL;
	}
	return temp.value;
}
