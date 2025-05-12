#include"minishell.h"

int	get_cwd(char **cwd)
{
	*cwd = getcwd(NULL, 0);
	if (!*cwd)
	{
		perror("getcwd");
		return(ERROR_GENERIC);
	}
	return (0);
}

int	set_pwd(t_data *data, char *env, char *old_pwd)
{
	t_env	*env_ptr;
	char	*cwd;

	if (!old_pwd)
	{
		if (get_cwd(&cwd) != 0)
			return (ERROR_GENERIC);
	}
	else
	{
		cwd = strdup(old_pwd);
		if (!cwd)
			return(ERROR_GENERIC);
	}
	env_ptr = find_env_name(data, env);
	if (!env_ptr)
	{
		if (!old_pwd)
			free(cwd);
		return(ERROR_GENERIC);
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

	home_ptr = find_env_name(data, "HOME");
	if (!home_ptr || !home_ptr->value)
	{
		print_error_msg("cd", ": HOME not set\n");
		return (ERROR_GENERIC);
	}
	if (set_pwd(data, "OLDPWD", NULL) != 0)
		return (ERROR_GENERIC);
	if (chdir(home_ptr->value) != 0)
	{
		perror("cd");
		return(ERROR_GENERIC);
	}
	if (set_pwd(data, "PWD", NULL) != 0)
		return (ERROR_GENERIC);
	return (0);
}
int	change_cur_dir(t_data *data, char *path)
{
	char *old_pwd;

	if (get_cwd(&old_pwd) != 0)
		return (ERROR_GENERIC);
	if (set_pwd(data, "OLDPWD", old_pwd) != 0)
	{
		free(old_pwd);
		return (ERROR_GENERIC);
	}
	if (chdir(path) != 0)
	{
		free(old_pwd);
		perror("cd");
		return(ERROR_GENERIC);
	}
	if (set_pwd(data, "PWD", NULL) != 0)
		return (ERROR_GENERIC);
	free(old_pwd);
	return (0);
}

int	ft_cd(t_data *data, t_command *cmd)
{
	char	*path;

	if (cmd->args[2])
	{
		print_error_msg("cd", ERR_TOO_MANY_ARGS);
		return(ERROR_GENERIC);
	}
	path = cmd->args[1];
	if (!path)
		return (go_home(data));
	if (path[0] == '-')
	{
		print_error_msg("cd", ERR_OPTIONS);
		return(ERROR_GENERIC);
	}
	return (change_cur_dir(data, path));
}
