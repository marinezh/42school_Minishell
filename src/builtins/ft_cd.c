#include "minishell.h"

int	get_cwd(char **cwd)
{
	*cwd = getcwd(NULL, 0);
	if (!*cwd)
	{
		perror("getcwd");
		return (ERR_GENERIC);
	}
	return (0);
}

int	set_pwd(t_data *data, char *env, char *old_pwd)
{
	t_env	*env_ptr;
	char	*cwd;

	if (!old_pwd && get_cwd(&cwd) != 0)
		return (ERR_GENERIC);
	if (old_pwd)
	{
		cwd = strdup(old_pwd);
		if (!cwd)
			return (ERR_GENERIC);
	}
	env_ptr = find_env_node(data, env);
	if (!env_ptr)
	{
		if (!old_pwd)
			free(cwd);
		return (ERR_GENERIC);
	}
	if (env_ptr->value)
		free(env_ptr->value);
	env_ptr->value = cwd;
	data->envp_f = 1;
	return (0);
}
int	go_home(t_data *data)
{
	t_env	*home_ptr;

	home_ptr = find_env_node(data, "HOME");
	if (!home_ptr || !home_ptr->value)
	{
		print_error_msg("cd", ": HOME not set\n");
		return (ERR_GENERIC);
	}
	if (set_pwd(data, "OLDPWD", NULL) != 0)
		return (ERR_GENERIC);
	if (chdir(home_ptr->value) != 0)
	{
		perror("cd");
		return (ERR_GENERIC);
	}
	if (set_pwd(data, "PWD", NULL) != 0)
		return (ERR_GENERIC);
	return (0);
}
int	change_cur_dir(t_data *data, char *path)
{
	char	*old_pwd;
	char	*cmd_name;

	if (get_cwd(&old_pwd) != 0)
		return (ERR_GENERIC);
	if (set_pwd(data, "OLDPWD", old_pwd) != 0)
	{
		free(old_pwd);
		return (ERR_GENERIC);
	}
	if (chdir(path) != 0)
	{
		cmd_name = ft_strjoin("cd: ", path);
		print_error_msg(cmd_name, MSG_NO_FILE);
		free(cmd_name);
		free(old_pwd);
		return (ERR_GENERIC);
	}
	if (set_pwd(data, "PWD", NULL) != 0)
	{
		ft_putstr_fd("cd: PWD not updated\n", 2);
		return (ERR_GENERIC);
	}
	free(old_pwd);
	return (0);
}

// void	print_error_msg(char *cmd, char *msg)
// {
//     ft_putstr_fd("minishell: ", STDERR_FILENO);
//     ft_putstr_fd(cmd, STDERR_FILENO);
//     ft_putstr_fd(msg, STDERR_FILENO);
// }

int	ft_cd(t_data *data, t_command *cmd)
{
	char	*path;
	int		args;

	args = count_args(cmd->args);
	if (args > 2)
	{
		print_error_msg("cd", MSG_TOO_MANY_ARGS);
		return (ERR_GENERIC);
	}
	path = cmd->args[1];
	if (!path)
		return (go_home(data));
	if (path[0] == '-')
	{
		print_error_msg("cd", MSG_NO_OPTIONS);
		return (ERR_GENERIC);
	}
	return (change_cur_dir(data, path));
}
