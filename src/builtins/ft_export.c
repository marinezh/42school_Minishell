/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikozhina <ikozhina@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 10:42:01 by ikozhina          #+#    #+#             */
/*   Updated: 2025/07/12 10:42:03 by ikozhina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

static int	update_var_value(t_data *data, t_env *env_var, char *arg)
{
	char	*ptr;
	char	*dup_str;
	char	*newkey;

	ptr	= ft_strchr(arg, '=');
	if (!ptr)
		return (0);
	if (!ft_strchr(env_var->key, '='))
	{
		newkey = ft_strjoin(env_var->key, "=");
		if (!newkey)
			return (1);
		free(env_var->key);
		env_var->key = newkey;
	}
	if (*(ptr + 1) == '\0')
		dup_str = ft_strdup("");
	else
		dup_str = ft_strdup(ptr + 1);
	if (!dup_str)
		return (1);
	free(env_var->value);
	env_var->value = dup_str;
	data->envp_f = 1;
	return (0);
}

static int	is_var_name_valid(char *arg, int *special_var)
{
	int	i;

    if (arg[0] == '_' && (arg[1] == '\0' || arg[1] == '='))
    {
        *special_var = 1;
        return(1);
    }
	if (!(ft_isalpha(arg[0]) || arg[0] == '_'))
		return (0);
	i = 1;
	while (arg[i] && arg[i] != '=')
	{
		if (!(ft_isalpha(arg[i]) || ft_isdigit(arg[i]) || arg[i] == '_'))
			return (0);
		i++;
	}
	return (1);
}

static int    process_env_var(t_data *data, char *env_var)
{
    t_env   *cur_env;
	t_env	*n_node;

    cur_env = find_env_node(data, env_var);
    if (cur_env)
	{
        if (update_var_value(data, cur_env, env_var) != 0)
		{
			free_env_list(&data->envp_list);
			return (1);
		}
		return (0);
	}
	n_node = create_env_node(env_var);
	if (!n_node)
	{
		free_env_list(&data->envp_list);
		return (1);
	}
	node_add_last(&data->envp_list, n_node);
	data->envp_f = 1;
	return (0);
}

static int	process_export_arg(t_data *data, char *arg, int *has_error)
{
	int		special_var;

	special_var = 0;
	if (arg[0] == '-')
	{
		print_error("export: ", arg, MSG_NO_OPTIONS);
		return (1);
	}
	if (!is_var_name_valid(arg, &special_var))
	{
		print_error("export: `", arg, MSG_INVALID_NAME);
		*has_error = 1;
	}
	else if (!special_var && process_env_var(data, arg) != 0)
	{
		print_error("export: ", arg, "memory allocation error\n");
		*has_error = 1;
	}
	return (0);
}

int	ft_export(t_data *data, t_command *cmd)
{
	int		i;
	int		has_error;

	if (!cmd->args[1])
		return (print_current_envp(data, cmd));
	has_error = 0;
	i = 0;
	while (cmd->args[++i])
	{
		if (process_export_arg(data, cmd->args[i], &has_error))
			return (1);
	}
	return (has_error);
}
