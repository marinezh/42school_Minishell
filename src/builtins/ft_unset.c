#include"minishell.h"

void	delete_node(t_data *data, t_env *node)
{
	t_env 	*cur;
	t_env	*tmp_next;

	if (!node)
		return ;
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
	free_env_node(node);
	data->envp_f = 1;
}

int	ft_unset(t_data *data, t_command *cmd)
{
	int		i;
	t_env	*env_node;

	if (!cmd->args || !cmd->args[1])
		return (0);
	i = 1;
	if (cmd->args[i][0] == '-')
	{
		print_error_msg("unset", MSG_NO_OPTIONS);
		return(ERR_GENERIC);
	}
	while (cmd->args[i])
	{
		env_node = find_env_node(data, cmd->args[i]);
		if (env_node)
			delete_node(data, env_node);
		i++;
	}
	env_node = NULL;
	return (0);
}

//bash unset doesn't check if var name valid identifier or not
//just checks if it exist as it is in env
//if can't find match, do nothing and return 0, no error