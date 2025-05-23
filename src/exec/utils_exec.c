#include"minishell.h"

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

t_env	*create_env_node(char *str)
{
    char	*ptr;
	char	*key;
	char	*value;
    t_env   *node;
	size_t	len;
	char *src;

    ptr = ft_strchr(str, '=');
    if (ptr)
	{
        len = (ptr - str) + 1;
		src = ptr + 1;
	}
	else
	{
		len = ft_strlen(str);
		src = NULL;
	}
    key = ft_strndup(str, len);
    if(!key)
        return (NULL);
    if (src)
    {
		value = ft_strdup(src);
		if (!value)
		{
        	free(key);
        	return(NULL);
		}
    }
	else
		value = NULL;
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

int	env_list_size(t_env *head)
{
	int		count;
	t_env	*cur; 

	count = 0;
	cur = head;
	while (cur)
	{
		count++;
		cur = cur->next;
	}
	return (count);
}

int	check_file_access(char *path)
{
	if (access(path, F_OK | X_OK) == 0)
		return(1);
	if (access(path, F_OK) == 0 && access(path, X_OK) != 0)
		return (-1);
	return (0);
}

// int	cmd_list_size(t_command *head)
// {
// 	int	count;
// 	t_command *cur;

// 	count = 0;
// 	cur = head;
// 	while (cur)
// 	{
// 		count++;
// 		cur = cur->next;
// 	}
// 	return(count);
// }
