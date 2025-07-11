#include "minishell.h"

int	set_pwd(t_data *data, char *env, char *old_pwd)
{
	t_env	*env_ptr;
	char	*cwd;

	if (!old_pwd)
		cwd = getcwd(NULL, 0);
	else
		cwd = ft_strdup(old_pwd);
	if (!cwd)
		return (ERR_GENERIC);
	env_ptr = find_env_node(data, env);
	if (!env_ptr)
	{
		free(cwd);
		return (ERR_GENERIC);
	}
	if (env_ptr->value)
		free(env_ptr->value);
	env_ptr->value = cwd;
	data->envp_f = 1;
	return (0);
}

int	prepare_old_pwd(t_data *data)
{
	char	*old_pwd;
	t_env	*pwd_env;

	old_pwd = getcwd(NULL, 0);
	if (!old_pwd)
	{
		pwd_env = find_env_node(data, "PWD");
		if (pwd_env && pwd_env->value)
			old_pwd = ft_strdup(pwd_env->value);
		else
			old_pwd = ft_strdup("");
		if (!old_pwd)
			return (ERR_GENERIC);
	}
	if (find_env_node(data, "OLDPWD") && set_pwd(data, "OLDPWD", old_pwd) != 0)
	{
		free(old_pwd);
		return (ERR_GENERIC);
	}
	free(old_pwd);
	return (0);
}

int	change_cur_dir(t_data *data, char *path)
{
	int	res;

	res = prepare_old_pwd(data);
	if (res != 0)
		return (ERR_GENERIC);
	if (chdir(path) != 0)
	{
		if (errno == EACCES)
			print_error("cd: ", path, MSG_NO_PERM);
		else if (errno == ENOENT)
			print_error("cd: ", path, MSG_NO_FILE);
		else if (errno == ENOTDIR)
			print_error("cd: ", path, ": Not a directory\n");
		else
			print_error("cd: ", path, strerror(errno));
		return (ERR_GENERIC);
	}
	if (find_env_node(data, "PWD") && set_pwd(data, "PWD", NULL) != 0)
		return (ERR_GENERIC);
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
	return (change_cur_dir(data, home_ptr->value));
}

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
		print_error("cd: ", path, MSG_NO_OPTIONS);
		return (2);
	}
	return (change_cur_dir(data, path));
}
