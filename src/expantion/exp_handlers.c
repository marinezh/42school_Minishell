#include "minishell.h"

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
// static int is_ambiguous_redirect(t_token *current, t_env *env_node)
// {
// 	// Remove the ft_tlsize check since we're just checking if prev exists
// 	if (current->prev &&
// 		(current->prev->type == REDIR_OUT || 
// 		 current->prev->type == REDIR_APPEND ||
// 		 current->prev->type == REDIR_IN) &&
// 		(ft_strchr(env_node->value, ' ') || env_node->value[0] == '\0'))
// 	{
// 		return 1;
// 	}
// 	return 0;
// }

// Handle variable expansion when variable is found
// static int process_found_variable(t_token *current, t_env *node, 
// 								 char *var_name, int *i, t_data *data)
// {
// 	// Check for ambiguous redirect case
// 	(void)data;
// 	if (is_ambiguous_redirect(current, node))
// 	{
// 		handle_error_arg(data, var_name, ERR_AMB_RED, 1);
// 		return 0;
// 	}
// 	// Replace the variable with its value
// 	if (!replace_variable(current, *i, ft_strlen(var_name), node->value))
// 	{
// 		handle_error_arg(data, "memory", ": allocation failed\n", 1);
// 		return 0;
// 	}
	
// 	return 1;
// }
static int process_found_variable(t_exp_params *params, t_env *node)
{
	// Check for ambiguous redirect case
	if (params->token->prev &&
		(params->token->prev->type == REDIR_OUT || 
		 params->token->prev->type == REDIR_APPEND ||
		 params->token->prev->type == REDIR_IN) &&
		(ft_strchr(node->value, ' ') || node->value[0] == '\0'))
	{
		handle_error_arg(params->data, params->var_name, ERR_AMB_RED, 1);
		return 0;
	}
	
	// Replace the variable with its value
	if (!replace_variable(params->token, *(params->index), 
						 ft_strlen(params->var_name), node->value))
	{
		handle_error_arg(params->data, "memory", ": allocation failed\n", 1);
		return 0;
	}
	
	return 1;
}

// Handle undefined variable case
static int process_undefined_variable(t_exp_params *params)
{
    if (!replace_undefined_variable(params->token, *(params->index), 
                                   ft_strlen(params->var_name)))
    {
        handle_error_arg(params->data, "memory", ": allocation failed\n", 1);
        return 0;
    }
    
    return 1;
}

// Main expansion handler function - removed the unused tokens parameter
// int handle_expantion(t_token *cur, t_data *data, int *i)
// {
//     char *var_name;
//     t_env *node;
//     int result;

//     // Extract variable name from token
//     var_name = extract_variable_name(&cur->value[*i + 1]);
//     if (!var_name || var_name[0] == '\0')
//     {
//         (*i)++;
//         return 1;
//     }
	
//     // Find variable in environment
//     node = find_env_node(data, var_name);
	
//     // Process based on whether variable was found
//     if (node && node->value)
//         result = process_found_variable(cur, node, var_name, i, data);
//     else
//         result = process_undefined_variable(cur, var_name, i, data);
	
//     free(var_name);
//     return result;
// }

// Main expansion handler function
int handle_expantion(t_token *cur, t_data *data, int *i)
{
	t_exp_params params;
	t_env *node;
	int result;

	params.token = cur;
	params.index = i;
	params.data = data;
	params.var_name = extract_variable_name(&cur->value[*i + 1]);
	if (!params.var_name || params.var_name[0] == '\0')
	{
		if (params.var_name)
			free(params.var_name);
		(*i)++;
		return 1;
	}
	// Find variable in environment
	node = find_env_node(data, params.var_name);
	// Process based on whether variable was found
	if (node && node->value)
		result = process_found_variable(&params, node);
	else
		result = process_undefined_variable(&params);
	
	free(params.var_name);
	return result;
}
