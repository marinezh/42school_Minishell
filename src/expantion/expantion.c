#include "minishell.h"

// int in_double_quotes(t_token *token)
// {
//     int len = ft_strlen(token->value);

//     if (len >= 2 && token->value[0] == '"' && token->value[len - 1] == '"')
//         return (1);
//     return (0);
// }

// static int	in_single_quotes(t_token *token)
// {
// 	int	len;

// 	len = ft_strlen(token->value);
// 	if (len >= 2 && token->value[0] == '\'' && token->value[len - 1] == '\'')
// 		return (1);
// 	return (0);
// }

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


int should_expand_variable(const char *str, int in_single)
{
	if (!str || !str[0] || str[0] != '$')
		return (0);

	// Inside single quotes, variables are not expanded
	if (in_single)
		return (0);

	// Handle $' or $" (skip expansion, treat as literal)
	if (str[1] == '\'' || str[1] == '\"')
		return (0);

	// Handle special case of $? (allowed)
	if (str[1] == '?')
		return (1);

	// Check if valid variable name starts
	if (ft_isalpha(str[1]) || str[1] == '_')
		return (1);

	// Otherwise, invalid variable start (e.g. space, punctuation, digit)
	return (0);
}

int	handle_status_var(t_token *token, int status, int *i)
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


// static int	handle_expantion(t_token *tokens, t_token *cur, t_data *data, int *i)
// {
// 	char	*var_name;
// 	t_env	*node;

// 	// if (!token || !token->value || !data || !i)
//     // 	return (0);
// 	//printf("EXPANTION FOUND at posision %d in token %s\n", *i, token->value);
// 	var_name = extract_variable_name(&cur->value[*i + 1]);
// 	if (!var_name || var_name[0] == '\0')
// 	{
// 		//free(var_name);
// 		(*i)++;
// 		return (1);
// 	}
// 	// printf("var_name!!! %s\n",var_name);
// 	node = find_env_node(data, var_name);

// 	if (node && node->value)
// 	{
// 		//printf("TOKEN PREV TYPE %d , %s, variable is %s\n", token->prev->type, ft_strchr(node->value, ' '), node->value );
// 		if (ft_tlsize(tokens) > 1 && cur->prev
// 			&& (cur->prev->type == REDIR_OUT
// 				|| cur->prev->type == REDIR_APPEND
// 				|| cur->prev->type == REDIR_IN)
// 				&& (ft_strchr(node->value, ' ') || node->value[0] == '\0'))
// 		{
// 			//printf("AMBIGOUS REDIRECT\n");
// 			handle_error_arg(data, var_name, ERR_AMB_RED, 1);
// 			//data->status = 1;
// 			return 0;
// 		}
// 		//printf("var_value %s\n", node->value);
// 		//printf("Found variable %s = %s\n", var_name, node->value);
// 		if (!replace_variable(cur, *i, ft_strlen(var_name), node->value))
// 		{
// 				handle_error_arg(data, "memory", ": allocation failed\n", 1);
// 				//*i += ft_strlen(var_name) + 1;
// 				free(var_name);
// 				return (0);
// 		}
// 		  //*i += strlen(node->value) - 1;
// 	}
// 	else
// 	{
// 		//printf("Variable %s not found, replacing with empty string\n",
// 			//var_name);
// 		if (!replace_undefined_variable(cur, *i, ft_strlen(var_name)))
// 		{
// 			handle_error_arg(data, "memory", ": allocation failed\n", 1);
// 			free(var_name);
// 			return (0);
// 		}
// 	}
// 	free(var_name);
// 	return (1);
// }

// Check if expansion will cause ambiguous redirect
// static int is_ambiguous_redirect(t_token *current, t_env *env_node)
// {
//     if (ft_tlsize(current) > 1 && current->prev &&
//         (current->prev->type == REDIR_OUT || 
//          current->prev->type == REDIR_APPEND ||
//          current->prev->type == REDIR_IN) &&
//         (ft_strchr(env_node->value, ' ') || env_node->value[0] == '\0'))
//     {
//         return 1;
//     }
//     return 0;
// }

// Handle variable expansion when variable is found


// Handle undefined variable case


// Check if expansion will cause ambiguous redirect - updated to not use ft_tlsize
static int is_ambiguous_redirect(t_token *current, t_env *env_node)
{
	// Remove the ft_tlsize check since we're just checking if prev exists
	if (current->prev &&
		(current->prev->type == REDIR_OUT || 
		 current->prev->type == REDIR_APPEND ||
		 current->prev->type == REDIR_IN) &&
		(ft_strchr(env_node->value, ' ') || env_node->value[0] == '\0'))
	{
		return 1;
	}
	return 0;
}

// Handle variable expansion when variable is found
static int process_found_variable(t_token *current, t_env *node, 
								 char *var_name, int *i, t_data *data)
{
	// Check for ambiguous redirect case
	if (is_ambiguous_redirect(current, node))
	{
		handle_error_arg(data, var_name, ERR_AMB_RED, 1);
		return 0;
	}
	
	// Replace the variable with its value
	if (!replace_variable(current, *i, ft_strlen(var_name), node->value))
	{
		handle_error_arg(data, "memory", ": allocation failed\n", 1);
		return 0;
	}
	
	return 1;
}

// Handle undefined variable case
static int process_undefined_variable(t_token *current, 
									 char *var_name, int *i, t_data *data)
{
	if (!replace_undefined_variable(current, *i, ft_strlen(var_name)))
	{
		handle_error_arg(data, "memory", ": allocation failed\n", 1);
		return 0;
	}
	
	return 1;
}

// Main expansion handler function - removed the unused tokens parameter
int handle_expantion(t_token *cur, t_data *data, int *i)
{
	char *var_name;
	t_env *node;
	int result;

	// Extract variable name from token
	var_name = extract_variable_name(&cur->value[*i + 1]);
	if (!var_name || var_name[0] == '\0')
	{
		(*i)++;
		return 1;
	}
	
	// Find variable in environment
	node = find_env_node(data, var_name);
	
	// Process based on whether variable was found
	if (node && node->value)
		result = process_found_variable(cur, node, var_name, i, data);
	else
		result = process_undefined_variable(cur, var_name, i, data);
	
	free(var_name);
	return result;
}

int expand_variables(t_token *tokens, t_data *data, int skip_after_heredoc)
{
	t_token *current;
	int i;
	int in_single;
	int in_double;
	int in_dollar_quote;  // New flag to track $"..." construct

	current = tokens;
	while (current)
	{
	  if ((!skip_after_heredoc || !current->prev || current->prev->type != HEREDOC) &&
			(current->type == WORD || current->type == FILE_NAME))

		{
			i = 0;
			in_single = 0;
			in_double = 0;
			in_dollar_quote = 0;  // Initialize new flag

			// Special handling for tokens that start with $"
			if (current->value[0] == '$' && (current->value[1] == '\"' || current->value[1] == '\''))
			{
				// Remove the leading $ by shifting everything left
				ft_memmove(current->value, current->value + 1, strlen(current->value));
				in_dollar_quote = 1;  // Mark that we're in a $" construct
			}

			while (current->value[i])
			{
				// Check for embedded $" patterns (not at start)
				if (i > 0 && current->value[i] == '$' && (current->value[i+1] == '\"' || current->value[i+1] == '\'')
					&& !in_single && !in_double)
				{
					// Remove the $ by shifting everything after it to the left
					memmove(&current->value[i], &current->value[i+1], 
						   strlen(&current->value[i+1]) + 1);
					in_dollar_quote = 1;
					continue;  // Re-process the current position (now a quote)
				}

				// Toggle quote state
				if (current->value[i] == '\'' && !in_double)
				{
					in_single = !in_single;
					i++;
					continue;
				}
				else if (current->value[i] == '\"' && !in_single)
				{
					in_double = !in_double;
					if (!in_double && in_dollar_quote)
						in_dollar_quote = 0;  // Exit $"..." construct
					i++;
					continue;
				}

				// Handle variable expansion - using existing code
				if (should_expand_variable(&current->value[i], in_single))
				{
					// Handle special case of $?
					if (current->value[i + 1] == '?')
					{
						if (!handle_status_var(current, data->status, &i))
						{
							handle_error_arg(data, "memory", ": allocation failed\n", 1);
							return (0);
						}
					}
					// Handle regular environment variables
					else
					{
						if (!handle_expantion(current, data, &i))
							return (0);
					}
					continue;
				}

				// If no expansion, just move forward
				i++;
			}
		}
		current = current->next;
	}
	return (1);
}

// void delete_empty_tokens(t_token **head)
// {
//     t_token *current = *head;
//     t_token *prev = NULL;
//     t_token *tmp;

//     while (current)
//     {
//         if (current->value && current->value[0] == '\0')
//         {
//             tmp = current;
//             if (prev) // not head
//                 prev->next = current->next;
//             else // head node is empty
//                 *head = current->next;

//             current = current->next;
//             free(tmp->value);
//             free(tmp);
//         }
//         else
//         {
//             prev = current;
//             current = current->next;
//         }
//     }
// }


// int	check_ambiguous_redirects(t_token *tokens, t_data *data)
// {
// 	t_token *curr = tokens;
// 	while (curr)
// 	{
// 		if (curr->prev && curr->prev->type == REDIR_OUT) // TOKEN_REDIR == 3
// 		{
// 			if (curr->value && (ft_strchr(curr->value, ' ') || curr->value[0] == '\0'))
// 			{
// 				handle_error_arg(data, curr->value, ERR_AMB_RED, 1);
// 				return (0);
// 			}
// 		}
// 		curr = curr->next;
// 	}
// 	return (1);
// }

	// if (token->prev && token->prev->type == 3 && (node->value[0] == '\0'))
	// {
	// 	printf("AMBIGOUS REDIRECT\n");
	// 	//handle_error_arg(data, var_name, "AMBIGOUS REDIRECT\n", 1);
	// 	data->status = 1;
	// 	return 0;
	// }
	// printf("Var value length: %zu\n", strlen(var_value));