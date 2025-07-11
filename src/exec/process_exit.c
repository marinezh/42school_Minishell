#include"minishell.h"

int	get_heredoc_exit_code(int wstatus)
{
	int	exit_code;

	if (WIFEXITED(wstatus))
		exit_code = WEXITSTATUS(wstatus);
	else if (WIFSIGNALED(wstatus))
		exit_code = 128 + WTERMSIG(wstatus);
	else
		exit_code = ERR_GENERIC;
	return (exit_code);
}

int	handle_heredoc_parent(pid_t pid)
{
	int	wstatus;
	int	exit_code;

	if (waitpid(pid, &wstatus, 0) != -1)
		exit_code = get_heredoc_exit_code(wstatus);
	else
	{
		perror("waitpid");
		exit_code = ERR_GENERIC;
	}
	return (exit_code);
}

int	get_pipe_exit_code(int wstatus)
{
	int	exit_code;

	exit_code = 0;
	if (WIFEXITED(wstatus))
		exit_code = WEXITSTATUS(wstatus);
	if (exit_code == 130)
		ft_putstr_fd("\n", STDERR_FILENO);
	else if (exit_code == 131)
		ft_putstr_fd("Quit (core dumped)\n", STDERR_FILENO);
	else
		exit_code = ERR_GENERIC;
	return (exit_code);
}