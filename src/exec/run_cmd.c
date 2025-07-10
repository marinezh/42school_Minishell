#include "minishell.h"

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

void	handle_child_process(t_data *data, t_command *cmd, char *path,
		char **args)
{
	char	**envp;

	envp = data->envp;
	reset_signals_to_default();
	if (execve(path, args, envp) == -1)
	{
		perror("execve");
		cleanup_process_data(data);
		free_command_list(cmd);
		free(path);
		if (errno == ENOENT)
			exit(ERR_CMD_NOT_FOUND);
		else if (errno == EACCES)
			exit(ERR_PERM_DENIED);
		else
			exit(ERR_GENERIC);
	}
}

int	get_pipe_exit_code(int wstatus)
{
	int	exit_code;

	exit_code = 0;
	if (WIFEXITED(wstatus))
		exit_code = WEXITSTATUS(wstatus);
	if (exit_code == 130)
	{
		ft_putstr_fd("\n", STDERR_FILENO);
	}
	else if (exit_code == 131)
	{
		ft_putstr_fd("Quit (core dumped)\n", STDERR_FILENO);
	}
	else
		exit_code = ERR_GENERIC;
	return (exit_code);
}
int	get_heredoc_exit_code_2(int wstatus)
{
	int	exit_code;

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
	return (exit_code);
}

int	get_execve_exit_code(t_data *data, int wstatus)
{
	int	exit_code;

	if (WIFEXITED(wstatus))
		exit_code = WEXITSTATUS(wstatus);
	else if (WIFSIGNALED(wstatus))
	{
		exit_code = 128 + WTERMSIG(wstatus);
		if (!data->is_pipe)
		{
			if (WTERMSIG(wstatus) == SIGINT)
				ft_putstr_fd("\n", STDERR_FILENO);
			else if (WTERMSIG(wstatus) == SIGQUIT)
				ft_putstr_fd("Quit (core dumped)\n", STDERR_FILENO);
		}
	}
	else
		exit_code = ERR_GENERIC;
	return (exit_code);
}

int	handle_heredoc_parent(pid_t pid)
{
	int	wstatus;
	int	exit_code;

	if (waitpid(pid, &wstatus, 0) != -1)
		exit_code = get_heredoc_exit_code_2(wstatus);
	else
	{
		perror("waitpid");
		exit_code = ERR_GENERIC;
	}
	return (exit_code);
}

int	handle_execve_parent(t_data *data, pid_t pid)
{
	int	wstatus;
	int	exit_code;

	if (waitpid(pid, &wstatus, 0) != -1)
		exit_code = get_execve_exit_code(data, wstatus);
	else
	{
		perror("waitpid");
		exit_code = ERR_GENERIC;
	}
	return (exit_code);
}

int	execute_cmd(t_data *data, t_command *cmd, char *path)
{
	pid_t	pid;
	int		exit_code;

	exit_code = 0;
	pid = create_process();
	if (pid == -1)
		return (1);
	if (pid == 0)
		handle_child_process(data, cmd, path, cmd->args);
	else
		exit_code = handle_execve_parent(data, pid);
	return (exit_code);
}
