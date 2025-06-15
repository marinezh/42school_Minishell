#include "minishell.h"


void remove_outer_quotes(t_token *tokens)
{
	t_token *current = tokens;
	
	while (current)
	{
		if (!current->value)
		{
			current = current->next;
			continue;
		}
		int i = 0, j = 0;
		char *input = current->value;
		char *result = malloc(ft_strlen(input) + 1);
		if (!result)
			return;
	
		while (input[i])
		{
			if (input[i] == '\'' || input[i] == '"')
			{
				char quote = input[i++];
				while (input[i] && input[i] != quote)
					result[j++] = input[i++];
				if (input[i] == quote)
					i++; // skip closing quote
			}
			else
				result[j++] = input[i++];
		}
		result[j] = '\0';
		free(current->value);
		current->value = result;
		current = current->next;
	}
}
