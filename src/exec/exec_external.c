#include "minishell.h"

int handle_error(t_data *data, char *arg, char *msg, int error_code)
{
	data->status = error_code;
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(arg, STDERR_FILENO);
	ft_putstr_fd(msg, STDERR_FILENO);
    return(data->status);
}

char *build_path(char *path, char *arg)
{
	char	*tmp;
	char	*res;

	tmp = ft_strjoin(path, "/");
	if (!tmp)
		return (NULL);
	res = ft_strjoin(tmp, arg);
	free(tmp);
	if (!res)
		return(NULL);
	return (res);
}

int	check_file_access(char *path)
{
	if (access(path, F_OK | X_OK) == 0)
		return(1);
	if (access(path, F_OK) == 0 && access(path, X_OK) != 0)
		return (-1);
	return (0);
}

char	*process_path(t_data *data, char *path_str, char *arg)
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
        handle_error(data, arg, MSG_NO_PERMISSION, ERR_PERM_DENIED);
		free(path);
		return (NULL);
	}
	free (path);
	return (NULL);
}

char	*parse_path_env(t_data *data, char *arg)
{
	t_env	*path_ptr;
	char	**path_dirs;
	char	*path_res;
	int		i;

	path_res = NULL;
	path_ptr = find_env_name(data, "PATH");
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
			break;
		i++;
	}
	free_double_array(path_dirs);
	return (path_res);
}

pid_t	create_process(void)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		return (-1);
	}
	return (pid);
}

void	handle_child_process(char *path, char **args, char **envp)
{
	if (execve(path, args, envp) == -1)
	{
		perror("execve");
		if (errno == ENOENT)
			exit(ERR_CMD_NOT_FOUND);
		else if (errno == EACCES)
			exit(ERR_PERM_DENIED);
		else
			exit(ERR_GENERIC);
	}
}

int	handle_parent_process(pid_t pid)
{
	int		wstatus;
	int		exit_code;

	waitpid(pid, &wstatus, 0);
	if (WIFEXITED(wstatus))
		exit_code = WEXITSTATUS(wstatus);
	else if (WIFSIGNALED(wstatus))
	{
		exit_code = 128 + WTERMSIG(wstatus);
		if (WTERMSIG(wstatus) == SIGINT)
			ft_putstr_fd("\n", STDERR_FILENO);
		else if (WTERMSIG(wstatus) == SIGQUIT)
			ft_putstr_fd("Quit (core dumped)\n", STDERR_FILENO);
	}
	else
		exit_code = ERR_GENERIC;
	return(exit_code);
}

int	execute_cmd(t_data *data, t_command *cmd, char *path)
{
	pid_t	pid;
	int		exit_code;

	exit_code = 0;
	pid = create_process();
	if (pid == -1)
		return (-1);
	if (pid == 0)
		handle_child_process(path, cmd->args, data->envp);
	else
		exit_code = handle_parent_process(pid);
	return (exit_code);
}
char *process_binary(t_data *data, char *arg)
{
    int		access_res;
    char	*path;

    access_res = check_file_access(arg);
    if (access_res == 1)
        path = arg;
    else if (access_res == -1)
    {
        handle_error(data, arg, MSG_NO_PERMISSION, ERR_PERM_DENIED);
        return(NULL);
    }
    else
    {
        handle_error(data, arg, MSG_NO_FILE, ERR_CMD_NOT_FOUND);
        return(NULL);
    }
    return (path);
}

int	run_external(t_data *data, t_command *cmd)
{
	char	*path;
	char	*path_to_free;
	int		exit_status;

    path_to_free = NULL;
    if (ft_strchr(cmd->args[0], '/'))
    {
        path = process_binary(data, cmd->args[0]);
        if (!path)
            return (data->status);
    }
	else
	{
		path = parse_path_env(data, cmd->args[0]);
		path_to_free = path;
		if (!path)
            return(handle_error(data, cmd->args[0], MSG_CMD_NOT_FOUND, 127));
	}
	exit_status = execute_cmd(data, cmd, path);
	data->status = exit_status;
	if (path_to_free)
		free(path_to_free);
	return (exit_status);
}

// bash command - test -x filename.c
// cat: test.txt: Permission denied - 1
// cat: adfas: No such file or directory - 1
// asdlfkja bash: kjsahfhsdf: command not found - 127

// 1) not exist
// 2) exist not executable
// 3) exist and executable

//bash make difference if (code the same 127)
// asldkfjasldkf - command not found
// or bin/adsfasdf - no such file or directory