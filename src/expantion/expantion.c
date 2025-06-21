#include "minishell.h"

// int in_double_quotes(t_token *token) 
// {
//     int len = ft_strlen(token->value);

//     if (len >= 2 && token->value[0] == '"' && token->value[len - 1] == '"')
//         return 1;
//     return 0;
// }

static int in_single_quotes(t_token *token)
{
	int len;

	len = ft_strlen(token->value);
	if (len >= 2 && token->value[0] == '\'' && token->value[len - 1] == '\'')
		return 1;
	return 0;
}

static void handle_status_var(t_token *token, int status, int *i)
{
	char *status_str = ft_itoa(status);
	if (!status_str)
		return;
	printf("STATUS %s\n", status_str);
	char *prefix = ft_substr(token->value, 0, *i);
	if (!prefix)
	{
		free(status_str);
		return;
	}
	printf("prefix if there is a STATUS %s\n", prefix);
	char *suffix = ft_strdup(&token->value[*i + 2]);
	if (!suffix)
	{
		free(status_str);
		free(prefix);
		return;
	}
	printf("suffix if there is a STATUS %s\n", prefix);
	char *new_value = ft_strjoin(prefix, status_str);
	if (!new_value)
	{
		free(status_str);
		free(prefix);
		free(suffix);
		return;
	}
	char *final_value = ft_strjoin(new_value, suffix);
	if (!final_value)
	{
		free(status_str);
		free(prefix);
		free(suffix);
		free(new_value);
		return;
	}
	free(token->value);
	token->value = final_value;

	*i = *i + ft_strlen(status_str) - 1;

	free(prefix);
	free(suffix);
	free(new_value);
	free(status_str);
}

static int handle_expantion(t_token *token, t_data *data, int *i)
{
	printf("EXPANTION FOUND at posision %d in token %s\n", *i, token->value);
	char *var_name = extract_variable_name(&token->value[*i + 1]);
	if (!var_name)
	{
		(*i)++;
		return 0;
	}
	// printf("var_name!!! %s\n",var_name);
	t_env *node = find_env_node(data, var_name); 
	//printf("Var value length: %zu\n", strlen(var_value));
	if (node && node->value)
	{
		printf("var_value %s\n", node->value);
		printf("Found variable %s = %s\n", var_name, node->value);
		int status = replace_variable(token, *i, ft_strlen(var_name), node->value);
		printf("STATUS %d\n ", status);
		if (!replace_variable(token, *i, ft_strlen(var_name), node->value))
		{
			//fprintf(stderr, "Memory allocation failed during variable replacement.\n");
			handle_error_arg(data, "memory", ": allocation failed\n", 1);
			//*i += ft_strlen(var_name) + 1;
			free(var_name);
			return 0;
		}
		
	}
	else
	{
		printf("Variable %s not found, replacing with empty string\n", var_name);
		if (!replace_undefined_variable(token, *i, ft_strlen(var_name)))
		{
			handle_error_arg(data, "memory", ": allocation failed\n", 1);
			free(var_name);
			return 0;
		}
	}
	free(var_name);
	return 1;
}

int expand_variables(t_token *token, t_data *data)
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
				{
					handle_status_var(current, data->status, &i);
					continue;
				}
					
				else if (current->value[i] == '$' && current->value[i + 1])
				{
					if(!handle_expantion(current, data, &i))
						return 0;
					continue;
				}
				else
					i++;
			}
		}
		current = current->next;
	}
	return 1;
}
