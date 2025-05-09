#include"minishell.h"

void	delete_node(t_data *data, t_env *node)
{
	t_env 	*cur;
	t_env	*tmp_next;

	tmp_next = node->next;
	cur = data->envp_list;
	if (data->envp_list == node)
		data->envp_list = tmp_next;
	else
	{
		while (cur && cur->next)
		{
			if (cur->next == node)
			{
				cur->next = tmp_next;
				break;
			}
			cur = cur->next;
		}
	}
	free(node);
	data->envp_f = 1;
}

int	ft_unset(t_data *data, t_command *cmd)
{
	int		i;
	t_env	*env_node;

	i = 1;
	if (cmd->args[i][0] == '-')
	{
		print_error_msg("unset", ERR_OPTIONS);
		return(ERROR_GENERIC);
	}
	while (cmd->args[i])
	{
		env_node = find_env_name(data, cmd->args[i]);
		if (env_node)
			delete_node(data, env_node);
		i++;
	}
	return (0);
}

//bash unset doesn't check if var name valid identifier or not
//just checks if it exist as it is in env
//if can't find match return 0, no error