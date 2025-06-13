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
		free(tmp->key);
		free(tmp->value);
		free(tmp);
	}
	*env = NULL;
}

void	free_fds(int **fds, int i)
{
	while (i >= 0)
	{
		free(fds[i]);
		i--;
	}
	free(fds);
}