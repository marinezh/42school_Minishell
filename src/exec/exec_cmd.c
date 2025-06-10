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

void	handle_child_process(char *path, char **args, char **envp)
{
	struct sigaction sa;

    ft_memset(&sa, 0, sizeof(sa));
    sa.sa_handler = SIG_DFL;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    sigaction(SIGINT, &sa, NULL);
    sigaction(SIGQUIT, &sa, NULL);
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