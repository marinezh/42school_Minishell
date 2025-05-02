#include "minishell.h"

t_env	*init_node(char *key, char *value)
{
	t_env	*ptr;

	ptr = calloc(1, sizeof(t_env));
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



int	env_list_size(t_env *env)
{
	int	count = 0;
	while (env)
	{
		count++;
		env = env->next;
	}
	return (count);
}

void	update_envp_array(t_data *data, t_env *envp_list)
{
	int	l_size;
	char	**ar_ptr;
	char	*tmp;
	int	i;
	t_env	*current;

	current = envp_list;
	i = 0;
	l_size = env_list_size(envp_list);
	ar_ptr = calloc(l_size + 1, sizeof(char *));
	if (!ar_ptr)
		return ;
	ar_ptr[l_size] = NULL;
	while (current != NULL && i < l_size)
	{

		tmp = ft_strjoin(current->key, "=");
		if(!tmp)
		{
			free_envp_array(ar_ptr);
			return ;
		}
		ar_ptr[i] = ft_strjoin(tmp, current->value);
		free(tmp);
		if (!ar_ptr[i])
		{
			free_envp_array(ar_ptr);
			return ;
		}
		i++;
		current = current->next;
	}
	if (data->envp)
		free_envp_array(data->envp);
	data->envp = ar_ptr;
}

void	init_data(t_data *data, char **env)
{
	data->cmd_names[0] = "pwd";
	data->cmd_names[1] = "echo";
	data->builtins[0] = ft_pwd;
	data->builtins[1] = ft_echo;

	int i = 2;
	while (i < 7)
	{
		data->cmd_names[i] = NULL;
		data->builtins[i] = NULL;
		i++;
	}
	data->envp_list = NULL;
	data->envp = NULL;
	init_envp_list(data, env);
	if (data->envp_list)
		update_envp_array(data, data->envp_list);
	// print_envp_list(data->envp_list);
	// int j = 0;
	// while (data->envp[j])
	// {
	// 	printf("%s\n", data->envp[j++]);
	// }
}
