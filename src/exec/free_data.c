#include "minishell.h"

void	free_double_array(char **arr)
{
	int	i;

	i = 0;
	if (arr)
	{
		while (arr[i])
		{
			free(arr[i]);
			i++;
		}
	}
	free(arr);
}

void	free_env_list(t_env **env)
{
	t_env	*tmp;
	t_env	*node;

	if (!env || !*env)
		return ;
	node = *env;
	while (node)
	{
		tmp = node;
		node = node->next;
		free_env_node(tmp);
	}
	*env = NULL;
}

void	free_env_node(t_env *node)
{
	if (node)
	{
		free(node->value);
		free(node->key);
		free(node);
	}
}

void	free_fds(int **fds, int i)
{
	while (i >= 0)
	{
		close(fds[i][0]);
		close(fds[i][1]);
		free(fds[i]);
		i--;
	}
	free(fds);
}

void	cleanup_process_data(t_data *data)
{
	free_env_list(&data->envp_list);
	free_double_array(data->envp);
	if (data->pids)
	{
		free(data->pids);
		data->pids = NULL;
	}
	rl_clear_history();
}