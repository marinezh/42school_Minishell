/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikozhina <ikozhina@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 10:32:44 by ikozhina          #+#    #+#             */
/*   Updated: 2025/07/14 14:37:56 by ikozhina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	build_envp_list(t_data *data, char **env)
{
	t_env	*node;
	int		i;
	int		fail;

	i = 0;
	fail = 0;
	while (env[i])
	{
		node = create_env_node(env[i]);
		if (node)
			node_add_last(&data->envp_list, node);
		else
			fail++;
		i++;
	}
	if (fail == 0)
		return (0);
	else
		return (-1);
}

static char	**fill_envp_array(t_env *envp_list, int list_size)
{
	int		i;
	t_env	*current;
	char	**envp_arr;

	envp_arr = ft_calloc(list_size + 1, sizeof(char *));
	if (!envp_arr)
		return (NULL);
	current = envp_list;
	i = 0;
	while (current)
	{
		if (current->value)
			envp_arr[i] = ft_strjoin(current->key, current->value);
		else
			envp_arr[i] = ft_strdup(current->key);
		if (!envp_arr[i])
		{
			free_double_array(envp_arr);
			envp_arr = NULL;
			return (NULL);
		}
		i++;
		current = current->next;
	}
	return (envp_arr);
}

int	rebuild_envp_array(t_data *data, t_env *envp_list)
{
	int		list_size;
	char	**envp_arr;

	list_size = env_list_size(envp_list);
	envp_arr = fill_envp_array(envp_list, list_size);
	if (!envp_arr)
	{
		ft_putstr_fd("Error: Memory allocation failed\n", 2);
		return (-1);
	}
	if (data->envp)
	{
		free_double_array(data->envp);
		data->envp = NULL;
	}
	data->envp = envp_arr;
	return (0);
}

int	init_data(t_data *data, char **env)
{
	ft_memset(data, 0, sizeof(t_data));
	data->cmd_names[0] = "pwd";
	data->cmd_names[1] = "echo";
	data->cmd_names[2] = "env";
	data->cmd_names[3] = "export";
	data->cmd_names[4] = "unset";
	data->cmd_names[5] = "cd";
	data->cmd_names[6] = "exit";
	data->builtins[0] = ft_pwd;
	data->builtins[1] = ft_echo;
	data->builtins[2] = ft_env;
	data->builtins[3] = ft_export;
	data->builtins[4] = ft_unset;
	data->builtins[5] = ft_cd;
	data->builtins[6] = ft_exit;
	if (build_envp_list(data, env) != 0)
		ft_putstr_fd("Warning: Some environment variables not loaded\n", 2);
	if (data->envp_list && (rebuild_envp_array(data, data->envp_list)) != 0)
		return (-1);
	return (0);
}
