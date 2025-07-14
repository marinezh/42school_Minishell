/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikozhina <ikozhina@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 10:38:30 by ikozhina          #+#    #+#             */
/*   Updated: 2025/07/14 14:38:31 by ikozhina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_env	*init_node(char *key, char *value)
{
	t_env	*ptr;

	ptr = ft_calloc(1, sizeof(t_env));
	if (!ptr)
		return (NULL);
	ptr->key = key;
	ptr->value = value;
	ptr->next = NULL;
	return (ptr);
}

static int	create_key_value(char *str, char **key, char **value)
{
	char	*ptr;
	size_t	len;

	ptr = ft_strchr(str, '=');
	if (ptr)
	{
		len = (ptr - str) + 1;
		*key = ft_strndup(str, len);
		if (!*key)
			return (0);
		*value = ft_strdup(ptr + 1);
		if (!*value)
		{
			free(*key);
			return (0);
		}
	}
	else
	{
		*key = ft_strdup(str);
		if (!*key)
			return (0);
		*value = NULL;
	}
	return (1);
}

t_env	*create_env_node(char *str)
{
	char	*key;
	char	*value;
	t_env	*node;

	if (!create_key_value(str, &key, &value))
		return (NULL);
	node = init_node(key, value);
	if (!node)
	{
		free(key);
		free(value);
		return (NULL);
	}
	return (node);
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
	DIR	*dir;

	if (access(path, F_OK) != 0)
		return (0);
	dir = opendir(path);
	if (dir)
	{
		closedir(dir);
		return (-2);
	}
	if (access(path, X_OK) != 0)
		return (-1);
	return (1);
}
