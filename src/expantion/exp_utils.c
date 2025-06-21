#include "minishell.h"

int replace_variable(t_token *token, int i, int var_len, const char *value)
{
	// char *prefix;
	// char *suffix;
	// char *new_value;
	// char *final_value;
	
	char *prefix = ft_substr(token->value, 0, i);
	printf("PREFIX IS %s\n", prefix);
	if (!prefix)
		return 0;
	char *suffix = ft_strdup(&token->value[i + var_len + 1]);
	printf("SUFFIX IS %s index is %i and var_len %d\n", suffix, i, var_len);
	if (!suffix)
	{
		free_strings(prefix, NULL);
		return 0;
	}
	char *new_value = ft_strjoin(prefix, value);
	printf("NEW VALUEIS %s\n", new_value);
	if (!new_value)
	{
		free_strings(prefix, suffix, NULL);
		return 0;
	}
	char *final_value = ft_strjoin(new_value, suffix);
	printf("FINAL VALUEIS %s\n", final_value);
	if (!final_value)
	{
		free_strings(prefix, suffix, new_value,NULL);
		return 0;
	}
	free(token->value);
	token->value = final_value;
	free_strings(prefix, suffix, new_value,NULL);
	return (1);
}

int replace_undefined_variable(t_token *token, int i, int var_len)
{
	char *prefix;
	char *suffix;
	char *final_value;

	prefix = ft_substr(token->value, 0, i);
	if (!prefix)
		return 0;
	suffix = ft_strdup(&token->value[i + var_len + 1]);
	if (!suffix)
	{
		free(prefix);
		return 0;
	}
	final_value = ft_strjoin(prefix, suffix);
	if (!final_value)
	{
		free(prefix);
		free(suffix);
		return 0;
	}
	free(token->value);
	token->value = final_value;
	free(prefix);
	free(suffix);
	return 1;
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
