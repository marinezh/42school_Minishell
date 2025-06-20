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
void replace_current_with_multiple(t_token **current, t_token *new_tokens)
{
	if (!current || !*current || !new_tokens)
		return;

	t_token *old = *current;
	t_token *tail = new_tokens;

	// Find the last token in the new list
	while (tail->next)
		tail = tail->next;

	// Link rest of old list after new tokens
	tail->next = old->next;

	// Replace current token pointer with new list head
	*current = new_tokens;

	// Free the original token
	free(old->value);
	free(old);
}

t_token *create_token_list_from_split(char **split)
{
	t_token *head = NULL;
	t_token *last = NULL;

	for (int i = 0; split[i]; i++)
	{
		t_token *new = malloc(sizeof(t_token));
		if (!new)
			return NULL;
		new->value = ft_strdup(split[i]);
		new->type = WORD;
		new->next = NULL;

		if (!head)
			head = new;
		else
			last->next = new;
		last = new;
	}
	return head;
}

void expand_variables(t_token *token, t_data *data)
{
	t_token *current = token;

	while (current)
	{
		if ((current->type == WORD || current->type == FILE_NAME) &&
			!in_single_quotes(current))
		{
			int i = 0;
			while (current->value[i])
			{
				if (current->value[i] == '$' && current->value[i + 1] == '?')
					handle_status_var(current, data->status, &i);
				else if (current->value[i] == '$' && current->value[i + 1])
				{
					handle_expantion(current, data, &i);
					continue;
				}
				i++;
			}

			// if (!current->in_db_quotes && ft_strchr(current->value, ' '))
			// {
			// 	char **split = quote_safe_split(current->value, ' ');
			// 	if (split && split[1])
			// 	{
			// 		t_token *new_tokens = create_token_list_from_split(split);
			// 		t_token *last = new_tokens;
			// 		while (last->next)
			// 			last = last->next;

			// 		last->next = current->next;
			// 		replace_current_with_multiple(&current, new_tokens);
			// 		current = last->next;
			// 		free_split_input(split);
			// 		continue; // already advanced current
			// 	}
			// 	free_split_input(split);
			// }
		}
		current = current->next;
	}
}
