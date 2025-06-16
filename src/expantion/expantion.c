#include "minishell.h"

// int in_double_quotes(t_token *token) 
// {
//     int len = ft_strlen(token->value);

//     if (len >= 2 && token->value[0] == '"' && token->value[len - 1] == '"')
//         return 1;
//     return 0;
// }

int in_single_quotes(t_token *token)
{
	int len;

	len = ft_strlen(token->value);
	if (len >= 2 && token->value[0] == '\'' && token->value[len - 1] == '\'')
		return 1;
	return 0;
}




void expand_variables(t_token *token, t_data *data)
{
	int i = 0;
	int j = 0;
	//t_env *current;
	t_token *current_token;

	// while (data->envp[i])
	// {
	// 	printf("ENV : %s\n", data->envp[i]);
	// 	i++;
	// }
	// printf("/////////////////////////////////////\n");
	// t_env *debug_env = data->envp_list;
	// printf("--- ENVIRONMENT VARIABLES DEBUG ---\n");
	// while (debug_env)
	// {
	// 	printf("ENV KEY: '%s', VALUE: '%s'\n", debug_env->key, debug_env->value);
	// 	debug_env = debug_env->next;
	// }
	// printf("--- END DEBUG ---\n");

	current_token = token;
	while(current_token)
	{
		if ((current_token->type == WORD || current_token->type == FILE_NAME) && !in_single_quotes(current_token))
		{
			i = 0;
			while(current_token->value[i])
			{
				if (current_token->value[i] == '$' && current_token->value[i + 1] == '?')
				{
					char *status_str = ft_itoa(data->status);
					printf("STATUS %s\n", status_str);
					char *prefix = ft_substr(current_token->value, 0, i);
					printf("prefix if there is a STATUS %s\n", prefix);
					char *suffix = ft_strdup(&current_token->value[i + 2]);
					printf("suffix if there is a STATUS %s\n", prefix);
					char *new_value = ft_strjoin(prefix, status_str);
					char *final_value = ft_strjoin(new_value, suffix);

					free(current_token->value);
					current_token->value = final_value;

					i += ft_strlen(status_str) - 1;

					free(prefix);
					free(suffix);
					free(new_value);
					free(status_str);
					
				}
				if (current_token->value[i] == '$' && current_token->value[i + 1])
				{
					printf("EXPANTION FOUND at posision %d in token %s\n", i, current_token ->value);
					char *var_name = ft_strdup(&current_token->value[i + 1]);
					j = 0;
					while (var_name[j] && (ft_isalnum(var_name[j]) || var_name[j] == '_'))
						j++;
					var_name[j] = '\0';
					
					printf("var_name!!! %s\n",var_name);
					t_env *node = find_env_node(data, var_name); 
					//printf("Var value length: %zu\n", strlen(var_value));
					
					if (node && node->value)
					{
					 	printf("var_value %s\n", node->value);
						printf("Found variable %s = %s\n", var_name, node->value);
						char *prefix = ft_substr(current_token->value, 0, i);
						if (!prefix)
						{
							free(var_name);
							continue;
						}
						printf("prefix is %s\n", prefix);
						char *suffix = ft_strdup(&current_token->value[i + j + 1]);
						if (!suffix)
						{
							free(prefix);
							free(var_name);
							continue;
						}
						printf("suffix is %s\n", suffix);
						char *new_value = ft_strjoin(prefix, node->value);
						if (!new_value)
						{
							free(prefix);
							free(suffix);
							free(var_name);
							continue;
						}
						printf("new_value %s\n", new_value);
						char *final_value = ft_strjoin(new_value, suffix);
						if (!final_value) {
							free(prefix);
							free(suffix);
							free(new_value);
							free(var_name);
							continue;
						}
						printf("final value %s\n", final_value);
						free(current_token->value);
						current_token->value = final_value;
						free(prefix);
						free(suffix);
						free(new_value);
					}
					else
					{
						printf("Variable %s not found, replacing with empty string\n", var_name);
						char *prefix = ft_substr(current_token->value, 0, i);
						if (!prefix)
						{
							free(var_name);
							continue;
						}
	
						char *suffix = ft_strdup(&current_token->value[i + j + 1]);
						if (!suffix)
						{
							free(prefix);
							free(var_name);
							continue;
						}
						// Directly join prefix and suffix with nothing in between
						char *final_value = ft_strjoin(prefix, suffix);
						if (!final_value)
						{
							free(prefix);
							free(suffix);
							free(var_name);
							continue;
						}
						free(current_token->value);
						current_token->value = final_value;
						free(prefix);
						free(suffix);
					}
					free(var_name);
				}
				i++;
			}
			//printf("       TOKENS!!![%d] %s\n", token->type, token->value);
		}
		current_token = current_token->next;
	}
}
