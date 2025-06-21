#include "minishell.h"

// int in_double_quotes(t_token *token)
// {
//     int len = ft_strlen(token->value);

//     if (len >= 2 && token->value[0] == '"' && token->value[len - 1] == '"')
//         return (1);
//     return (0);
// }

static int	in_single_quotes(t_token *token)
{
	int	len;

	len = ft_strlen(token->value);
	if (len >= 2 && token->value[0] == '\'' && token->value[len - 1] == '\'')
		return (1);
	return (0);
}

// static int	handle_status_var(t_token *token, int status, int *i)
// {
// 	t_exp_parts	parts;

// 	parts.status_str = ft_itoa(status);
// 	if (!parts.status_str)
// 		return 0;
// 	parts.prefix = ft_substr(token->value, 0, *i);
// 	if (!parts.prefix )
// 		return (free_strings(parts.status_str, NULL), 0);
// 	parts.suffix = ft_strdup(&token->value[*i + 2]);
// 	if (!parts.suffix)
// 		return (free_strings(parts.status_str, parts.prefix, NULL), 0);
// 	parts.new_value = ft_strjoin(parts.prefix, parts.status_str);
// 	if (!parts.new_value)
// 		return (free_strings(parts.status_str, parts.prefix, parts.suffix, NULL), 0);
// 	parts.final_value = ft_strjoin(parts.new_value, parts.suffix);
// 	if (!parts.final_value)
// 	{
// 		free(parts.new_value);
// 		return (free_strings(parts.status_str, parts.prefix, parts.suffix, NULL),0);
// 	}
// 	free(token->value);
// 	token->value = parts.final_value;
// 	free_strings(parts.status_str, parts.prefix, parts.suffix, NULL);
// 	free(parts.new_value);
// 	return (1);
// }
static int	handle_status_var(t_token *token, int status, int *i)
{
	t_exp_parts	parts;

	ft_bzero(&parts, sizeof(t_exp_parts));
	parts.status_str = ft_itoa(status);
	if (!parts.status_str)
		return (0);
	parts.prefix = ft_substr(token->value, 0, *i);
	if (!parts.prefix)
		return (free_exp_parts(&parts), 0);
	parts.suffix = ft_strdup(&token->value[*i + 2]);
	if (!parts.suffix)
		return (free_exp_parts(&parts), 0);
	parts.new_value = ft_strjoin(parts.prefix, parts.status_str);
	if (!parts.new_value)
		return (free_exp_parts(&parts), 0);
	parts.final_value = ft_strjoin(parts.new_value, parts.suffix);
	if (!parts.final_value)
		return (free_exp_parts(&parts), 0);
	free(token->value);
	token->value = parts.final_value;
	free(parts.status_str);
	free(parts.prefix);
	free(parts.suffix);
	free(parts.new_value);
	return (1);
}


static int	handle_expantion(t_token *token, t_data *data, int *i)
{
	char	*var_name;
	t_env	*node;

	printf("EXPANTION FOUND at posision %d in token %s\n", *i, token->value);
	var_name = extract_variable_name(&token->value[*i + 1]);
	if (!var_name)
	{
		(*i)++;
		return (0);
	}
	// printf("var_name!!! %s\n",var_name);
	node = find_env_node(data, var_name);
	// printf("Var value length: %zu\n", strlen(var_value));
	if (node && node->value)
	{
		printf("var_value %s\n", node->value);
		printf("Found variable %s = %s\n", var_name, node->value);
		if (!replace_variable(token, *i, ft_strlen(var_name), node->value))
		{
				handle_error_arg(data, "memory", ": allocation failed\n", 1);
				//*i += ft_strlen(var_name) + 1;
				free(var_name);
				return (0);
		}
	}
	else
	{
		printf("Variable %s not found, replacing with empty string\n",
			var_name);
		if (!replace_undefined_variable(token, *i, ft_strlen(var_name)))
		{
			handle_error_arg(data, "memory", ": allocation failed\n", 1);
			free(var_name);
			return (0);
		}
	}
	free(var_name);
	return (1);
}

int	expand_variables(t_token *token, t_data *data)
{
	t_token	*current;
	int		i;

	current = token;
	while (current)
	{
		if ((current->type == WORD || current->type == FILE_NAME)
			&& !in_single_quotes(current))
		{
			i = 0;
			while (current->value[i])
			{
				if (current->value[i] == '$' && current->value[i + 1] == '?')
				{
					if (!handle_status_var(current, data->status, &i))
					{
						handle_error_arg(data, "memory", ": allocation failed\n", 1);
						return (0);
					}
					continue ;
				}
				else if (current->value[i] == '$' && current->value[i + 1])
				{
					if (!handle_expantion(current, data, &i))
						return (0);
					continue ;
				}
				else
					i++;
			}
		}
		current = current->next;
	}
	return (1);
}
