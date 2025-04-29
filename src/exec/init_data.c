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
t_env   *create_env_node(char *str)
{
    char	*ptr;
	char	*key;
	char	*value;
    t_env   *node;

    ptr = ft_strchr(str, '=');
    if (!ptr)
        return (NULL);
    key = ft_strndup(str, ptr - str);
    if(!key)
        return (NULL);
    value = ft_strdup(ptr + 1);
    if (!value)
    {
        free(key);
        return(NULL);
    }
    node = init_node(key, value);
    if (!node)
    {
        free(key);
        free(value);
        return(NULL);
    }
    return (node);
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
	size_t	i;

	i = 0;
	while (env[i])
	{
        node = create_env_node(env[i]);
        if (node)
		    node_add_last(&data->envp_list, node);
		i++;
	}
}

void	print_envp_list(t_env *envp_list)
{
	t_env	*list = envp_list;

	while (list)
	{
		printf("Key: [%s] | Value: [%s]\n", list->key, list->value);
		list = list->next;
	}
}

void	init_data(t_data *data, char **env)
{
	
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
	// print_envp_list(data->envp_list);
}