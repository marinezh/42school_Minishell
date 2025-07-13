/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_external.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikozhina <ikozhina@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 10:34:38 by ikozhina          #+#    #+#             */
/*   Updated: 2025/07/12 11:00:22 by ikozhina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*build_path(char *path, char *arg)
{
	char	*tmp;
	char	*res;

	tmp = ft_strjoin(path, "/");
	if (!tmp)
		return (NULL);
	res = ft_strjoin(tmp, arg);
	free(tmp);
	if (!res)
		return (NULL);
	return (res);
}

static char	*process_path(t_data *data, char *path_str, char *arg)
{
	char	*path;
	int		access_res;

	path = build_path(path_str, arg);
	if (!path)
		return (NULL);
	access_res = check_file_access(path);
	if (access_res == 1)
		return (path);
	if (access_res == -1)
	{
		handle_error_arg(data, arg, MSG_NO_PERM, ERR_PERM_DENIED);
		free(path);
		return (NULL);
	}
	free(path);
	return (NULL);
}

static char	*parse_path_env(t_data *data, char *arg)
{
	t_env	*path_ptr;
	char	**path_dirs;
	char	*path_res;
	int		i;

	path_res = NULL;
	path_ptr = find_env_node(data, "PATH");
	if (!path_ptr)
		return (NULL);
	path_dirs = ft_split(path_ptr->value, ':');
	if (!path_dirs || !path_dirs[0])
	{
		free_double_array(path_dirs);
		return (NULL);
	}
	i = 0;
	while (path_dirs[i])
	{
		path_res = process_path(data, path_dirs[i], arg);
		if (path_res)
			break ;
		i++;
	}
	free_double_array(path_dirs);
	return (path_res);
}

static char	*process_binary(t_data *data, char *path)
{
	int	access_res;

	access_res = check_file_access(path);
	if (access_res == 1)
		return (path);
	if (access_res == -1)
		handle_error_arg(data, path, MSG_NO_PERM, ERR_PERM_DENIED);
	else if (access_res == -2)
		handle_error_arg(data, path, MSG_IS_DIR, ERR_PERM_DENIED);
	else
		handle_error_arg(data, path, MSG_NO_FILE, ERR_CMD_NOT_FOUND);
	return (NULL);
}

int	run_external(t_data *data, t_command *cmd)
{
	char	*path;
	char	*path_to_free;
	int		exit_status;

	path_to_free = NULL;
	if (ft_strchr(cmd->args[0], '/'))
		path = process_binary(data, cmd->args[0]);
	else
	{
		path = parse_path_env(data, cmd->args[0]);
		path_to_free = path;
		if (!path)
			handle_error_arg(data, cmd->args[0], MSG_CMD_NOT_FOUND, 127);
	}
	if (!path)
		return (data->status);
	exit_status = execute_cmd(data, cmd, path);
	data->status = exit_status;
	if (path_to_free)
		free(path_to_free);
	return (exit_status);
}
