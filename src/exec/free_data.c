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
void	safe_free_pointer(void **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
	}
}