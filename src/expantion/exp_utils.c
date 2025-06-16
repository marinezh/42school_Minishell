#include "minishell.h"

void replace_undefined_variable(t_token *token, int i, int var_len)
{
	char *prefix;
	char *suffix;
	char *final_value;

	prefix = ft_substr(token->value, 0, i);
	if (!prefix)
		return;
	suffix = ft_strdup(&token->value[i + var_len + 1]);
	if (!suffix)
	{
		free(prefix);
		return;
	}
	final_value = ft_strjoin(prefix, suffix);
	if (!final_value)
	{
		free(prefix);
		free(suffix);
		return;
	}
	free(token->value);
	token->value = final_value;
	free(prefix);
	free(suffix);
}
