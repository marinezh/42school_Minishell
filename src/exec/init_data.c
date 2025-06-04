#include "minishell.h"

void	build_envp_list(t_data *data, char **env)
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

void	update_envp_array(t_data *data, t_env *envp_list)
{
	int	list_size;
	char	**ar_ptr;
	int		i;
	t_env	*current;

	list_size = env_list_size(envp_list);
	ar_ptr = calloc(list_size + 1, sizeof(char *));
	if (!ar_ptr)
		return ;
	current = envp_list;
	i = 0;
	while (current != NULL && i < list_size)
	{
		if (current->value)
			ar_ptr[i] = ft_strjoin(current->key, current->value);
		else
			ar_ptr[i] = ft_strdup(current->key);
		if (!ar_ptr[i])
		{
			free_double_array(ar_ptr);
			ar_ptr = NULL;
			return ;
		}
		i++;
		current = current->next;
	}
	if (data->envp)
	{
		free_double_array(data->envp);
		data->envp = NULL;
	}
	data->envp = ar_ptr;
}

void	init_data(t_data *data, char **env)
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
	build_envp_list(data, env);
	if (data->envp_list)
		update_envp_array(data, data->envp_list);
}
