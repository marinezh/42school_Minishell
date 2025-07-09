#include"minishell.h"

static void	delete_env_var(t_data *data, char *name)
{
	t_env	*env_node;
	t_env 	*cur;
	t_env	*tmp_next;

	env_node = find_env_node(data, name);
	if (!env_node)
		return ;
	tmp_next = env_node->next;
	cur = data->envp_list;
	if (data->envp_list == env_node)
		data->envp_list = tmp_next;
	else
	{
		while (cur && cur->next)
		{
			if (cur->next == env_node)
			{
				cur->next = tmp_next;
				break;
			}
			cur = cur->next;
		}
	}
	free_env_node(env_node);
	data->envp_f = 1;
}

static int	is_name_valid(char *name)
{
	int	i;

	if (!(ft_isalpha(name[0]) || name[0] == '_'))
		return (0);
	i = 1;
	while (name[i])
	{
		if (name[i] == '=')
			return (0);
		if (!(ft_isalpha(name[i]) || ft_isdigit(name[i]) || name[i] == '_'))
			return (0);
		i++;
	}
	return (1);
}

int	ft_unset(t_data *data, t_command *cmd)
{
	int		i;
	int		exit_status;

	i = 1;
	exit_status = 0;
	if (!cmd->args || !cmd->args[1])
		return (0);
	if (cmd->args[i][0] == '-' && cmd->args[i][1] != '\0')
	{
		print_error_msg("unset", MSG_NO_OPTIONS);
		return(ERR_GENERIC);
	}
	while (cmd->args[i])
	{
		if (!is_name_valid(cmd->args[i]))
		{
			print_error("unset: `", cmd->args[i], MSG_INVALID_NAME);
			exit_status = ERR_GENERIC;
		}
		else
			delete_env_var(data, cmd->args[i]);
		i++;
	}
	return (exit_status);
}
