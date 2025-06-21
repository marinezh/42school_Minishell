#include "minishell.h"

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
