#include "minishell.h"

int	replace_variable(t_token *token, int i, int var_len, const char *value)
{
	char	*prefix;
	char	*suffix;
	char	*new_value;
	char	*final_value;

	prefix = ft_substr(token->value, 0, i);
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
