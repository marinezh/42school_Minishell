#include "minishell.h"

int	replace_variable(t_token *token, int i, int var_len, const char *value)
{
	char	*prefix;
	char	*suffix;
	char	*new_value;
	char	*final_value;

	prefix = ft_substr(token->value, 0, i); // checked
	if (!prefix)
		return (0);
	new_value = ft_strjoin(prefix, value); //checked
	if (!new_value)
		return (free_strings(prefix, NULL), 0);
	suffix = ft_strdup(&token->value[i + var_len + 1]); // checked
	if (!suffix)
		return (free_strings(prefix, new_value, NULL), 0);
	final_value = ft_strjoin(new_value, suffix);  //checked
	if (!final_value)
		return (free_strings(prefix, suffix, new_value, NULL), 0);
	free(token->value);
	token->value = final_value;
	free_strings(prefix, suffix, new_value, NULL);
	return (1);
}

int	replace_undefined_variable(t_token *token, int i, int var_len)
{
	char	*prefix;
	char	*suffix;
	char	*final_value;

	prefix = ft_substr(token->value, 0, i); // checked
	if (!prefix)
		return (0);
	suffix = ft_strdup(&token->value[i + var_len + 1]); 
	if (!suffix)
		return (free_strings(prefix, NULL), 0);
	final_value = ft_strjoin(prefix, suffix);
	if (!final_value)
		return (free_strings(prefix, suffix, NULL), 0);
	free(token->value);
	token->value = final_value;
	free_strings(prefix, suffix, NULL);
	return (1);
}

static int	process_found_variable(t_exp_params *params, t_env *node)
{
	if (params->token->prev && (params->token->prev->type == REDIR_OUT
			|| params->token->prev->type == REDIR_APPEND
			|| params->token->prev->type == REDIR_IN)
		&& (ft_strchr(node->value, ' ') || node->value[0] == '\0'))
	{
		handle_error_arg(params->data, params->var_name, ERR_AMB_RED, 1);
		return (0);
	}
	if (!replace_variable(params->token, *(params->index),
			ft_strlen(params->var_name), node->value))
	{
		handle_error_arg(params->data, "memory", ": allocation failed\n", 1);
		return (0);
	}
	return (1);
}

static int	process_undefined_variable(t_exp_params *params)
{
	if (!replace_undefined_variable(params->token, *(params->index),
			ft_strlen(params->var_name)))
	{
		handle_error_arg(params->data, "memory", ": allocation failed\n", 1);
		return (0);
	}
	return (1);
}

int	handle_expantion(t_token *cur, t_data *data, int *i)
{
	t_exp_params	params;
	t_env			*node;
	int				result;

	params.token = cur;
	params.index = i;
	params.data = data;
	params.var_name = extract_variable_name(&cur->value[*i + 1]);
	if (!params.var_name || params.var_name[0] == '\0')
	{
		if (params.var_name)
			free(params.var_name);
		(*i)++;
		return (1);
	}
	node = find_env_node(data, params.var_name);
	if (node && node->value)
		result = process_found_variable(&params, node);
	else
		result = process_undefined_variable(&params);
	free(params.var_name);
	return (result);
}
