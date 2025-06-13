#include "minishell.h"

char *get_env_value(t_env *env_list, const char *key)
{
	//printf("Searching for environment key: '%s'\n", key);
	while (env_list)
	{
		char *temp_key = ft_strdup(env_list->key); // Create a temporary copy to manipulate
		if (!temp_key)
			return NULL;
		
		char *equals = ft_strchr(temp_key, '=');
		if (equals)
			*equals = '\0'; // Remove equals sign if present
			
		printf("Comparing with: '%s' (original: '%s')\n", temp_key, env_list->key);
		if (ft_strcmp(temp_key, key) == 0) // Compare without equals sign
		{
			printf("MATCH FOUND! Value: '%s'\n", env_list->value);
			free(temp_key);
			return env_list->value;
		}
		free(temp_key);
		env_list = env_list->next;
	}
	printf("KEY NOT FOUND in environment\n");
	return NULL;
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
		if (current_token->type == WORD)
		{
			i = 0;
			while(current_token->value[i])
			{
				if (current_token->value[i] == '$' && current_token->value[i + 1])
				{
					printf("EXPANTION FOUND at posision %d in token %s\n", i, current_token ->value);
					char *var_name = ft_strdup(&current_token->value[i + 1]);
					j = 0;
					while (var_name[j] && (ft_isalnum(var_name[j]) || var_name[j] == '_'))
						j++;
					var_name[j] = '\0';
					
					printf("var_name %s\n",var_name);
					t_env *node = find_env_node(data, var_name);
					// char *var_value = get_env_value(data->envp_list, var_name);
					//printf("Var value length: %zu\n", strlen(var_value));
					printf("var_value %s\n", node->value);
					if (node->value)
					{
					 	printf("Found variable %s = %s\n", var_name, node->value);

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
