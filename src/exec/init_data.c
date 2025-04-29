#include "minishell.h"

t_env	*init_node(char *key, char *value)
{
	t_env	*ptr;

	ptr = malloc(sizeof(t_env));
	if (!ptr)
		return (NULL);
	ptr->key = key;
	ptr->value = value;
	ptr->next = NULL;
	return (ptr);
}

void	node_add_last(t_env **envp_list, t_env *new_node)
{
	t_env	*ptr;

	ptr = *envp_list;
	if (!envp_list || !new_node)
		return ;
	if (*envp_list == NULL)
	{
		*envp_list = new_node;
		return ;
	}
	while (ptr->next != NULL)
		ptr = ptr->next;
	ptr->next = new_node;
}

void	init_envp_list(t_data *data, char **env)
{
	t_env	*node;
	char	*ptr;
	size_t	i;
	char	*key;
	char	*value;

	i = 0;
	while (env[i])
	{
		ptr = ft_strchr(env[i], '=');
		if (!ptr)
		{
			i++;
			continue;
		}
		key = ft_strndup(env[i], ptr - env[i]);
		value = ft_strdup(ptr + 1);
		node = init_node(key, value);
		if (!key || !value || !node)
		{
			free(key);
			free(value);
			i++;
			continue;
		}
		node_add_last(&data->envp_list, node);
		i++;
	}
}

void	print_envp_list(t_env *envp_list)
{
	t_env	*list = envp_list;

	while (list)
	{
		printf("key: %s | value: %s\n", list->key, list->value);
		list = list->next;
	}
}

void	init_data(t_data *data, char **env)
{
	printf("here");
	data->cmd_names[0] = "pwd";
	data->builtins[0] = ft_pwd;

	int i = 1;
	while (i < 7)
	{
		data->cmd_names[i] = NULL;
		data->builtins[i] = NULL;
		i++;
	}
	data->envp_list = NULL;
	init_envp_list(data, env);
	print_envp_list(data->envp_list);
}