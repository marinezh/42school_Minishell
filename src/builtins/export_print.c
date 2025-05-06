#include "minishell.h"

void	print_current_envp(t_data *data, t_command *cmd)
{
	// int i;

	// i = 0;
	// (void)cmd;
	// if (data->envp_f)
	// {
	// 	update_envp_array(data, data->envp_list);
	// 	data->envp_f = 0;
	// }
	// if (data->envp)
	// {
	// 	while (data->envp[i])
	// 	{
	// 		printf("declare -x %s\n", data->envp[i]);
	// 		i++;
	// 	}
	// }
	size_t	list_len;
	t_env	**arr_nodes;

	list_len = env_list_size(data->envp_list);
	arr_nodes = malloc(sizeof(t_env *) * list_len);
	if (!arr_nodes)
		return ;



}