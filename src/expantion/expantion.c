#include "minishell.h"

// int in_double_quotes(t_token *token) 
// {
//     int len = ft_strlen(token->value);

//     if (len >= 2 && token->value[0] == '"' && token->value[len - 1] == '"')
//         return 1;
//     return 0;
// }

int in_single_quotes(t_token *token)
{
	int len;

	len = ft_strlen(token->value);
	if (len >= 2 && token->value[0] == '\'' && token->value[len - 1] == '\'')
		return 1;
	return 0;
}

char *extract_variable_name(const char *input)
{
	int j;

	j = 0;
	while (input[j] && (ft_isalnum(input[j]) || input[j] == '_'))
		j++;
	char *var_name = ft_substr(input, 0, j);
	return var_name;
}

void expand_variables(t_token *token, t_data *data)
{
	int i;

	t_token *current;

	current = token;
	while(current)
	{
		if ((current->type == WORD || current->type == FILE_NAME) &&
			 !in_single_quotes(current))
		{
			i = 0;
			while(current->value[i])
			{
				if (current->value[i] == '$' && current->value[i + 1] == '?')
					handle_status_var(current, data->status, &i);
				if (current->value[i] == '$' && current->value[i + 1])
				{
					handle_expantion(current, data, &i);
					continue;
				}
				i++;
			}
		}
		current = current->next;
	}
}
