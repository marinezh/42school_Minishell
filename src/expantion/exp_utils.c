#include "minishell.h"

void replace_variable(t_token *token, int i, int var_len, const char *value)
{
	char *prefix = ft_substr(token->value, 0, i);
	if (!prefix)
		return;
	char *suffix = ft_strdup(&token->value[i + var_len + 1]);
	if (!suffix)
	{
		free(prefix);
		return;
	}
	char *new_value = ft_strjoin(prefix, value);
	if (!new_value)
	{
		free(prefix);
		free(suffix);
		return;
	}
	char *final_value = ft_strjoin(new_value, suffix);
	if (!final_value)
	{
		free(prefix);
		free(suffix);
		free(new_value);
		return;
	}
	free(token->value);
	token->value = final_value;

	free(prefix);
	free(suffix);
	free(new_value);
}
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
void handle_status_var(t_token *token, int status, int *i)
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

void handle_expantion(t_token *token, t_data *data, int *i)
{
	printf("EXPANTION FOUND at posision %d in token %s\n", *i, token->value);
	char *var_name = extract_variable_name(&token->value[*i + 1]);
	if (!var_name)
	{
		(*i)++;
		return;
	}
	// printf("var_name!!! %s\n",var_name);
	t_env *node = find_env_node(data, var_name); 
	//printf("Var value length: %zu\n", strlen(var_value));
	if (node && node->value)
	{
		printf("var_value %s\n", node->value);
		printf("Found variable %s = %s\n", var_name, node->value);
		replace_variable(token, *i, ft_strlen(var_name), node->value);
	}
	else
	{
		printf("Variable %s not found, replacing with empty string\n", var_name);
		replace_undefined_variable(token, *i, ft_strlen(var_name));
	}
	free(var_name);
}