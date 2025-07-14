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
	new_value = ft_strjoin(prefix, value);
	if (!new_value)
		return (free_strings(prefix, NULL), 0);
	suffix = ft_strdup(&token->value[i + var_len + 1]);
	if (!suffix)
		return (free_strings(prefix, new_value, NULL), 0);
	final_value = ft_strjoin(new_value, suffix);
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

	prefix = ft_substr(token->value, 0, i);
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
	// printf("[%d] '%s' (len: %zu)\n", i, token->value, strlen(token->value));
	// printf("[%d] >%s<\n", i, token->value);

	return (1);
}

char	*extract_variable_name(const char *input)
{
	int		j;
	char	*var_name;

	j = 0;
	while (input[j] && (ft_isalnum(input[j]) || input[j] == '_'))
		j++;
	var_name = ft_substr(input, 0, j);
	return (var_name);
}
int	ft_tlsize(t_token *tokens)
{
	int		count;
	t_token	*pnt;

	pnt = tokens;
	count = 0;
	while (pnt != NULL)
	{
		count++;
		pnt = pnt->next;
	}
	return (count);
}
int process_status_var(t_token *token, t_data *data, int *i)
{
    if (!handle_status_var(token, data->status, i))
    {
        handle_error_arg(data, "memory", ": allocation failed\n", 1);
        return (0);
    }
    return (1);
}

int process_expantion(t_token *token, t_data *data, int *i)
{
	if (!handle_expantion(token, data, i))
	{
		//handle_error_arg(data, "memory", ": allocation failed\n", 1);
		return (0);
	}
	return (1);
}
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