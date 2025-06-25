#include "minishell.h"

int	redirect_stream(t_data *data, int old_fd, int new_fd)
{
	if (dup2(old_fd, new_fd) == -1)
	{
		perror("dup2");
		data->status = 1;
		return (-1);
	}
	return (new_fd);
}

int	copy_stream(int fd)
{
	int	saved_stream;

	saved_stream = dup(fd);
	if (saved_stream == -1)
		perror("dup");
	return (saved_stream);
}

void	restore_streams(t_data *data, int orig_stdin, int orig_stdout)
{
	if (orig_stdin != -1)
	{
		if (redirect_stream(data, orig_stdin, 0) == -1)
			perror("restore stdin");
		close(orig_stdin);
	}
	if (orig_stdout != -1)
	{
		if (redirect_stream(data, orig_stdout, 1) == -1)
			perror("restore stdout");
		close(orig_stdout);
	}
}

int	redirect_io(t_data *data, t_command *cmd, int *orig_in, int *orig_out)
{
	*orig_in = -1;
	*orig_out = -1;
	if (cmd->in)
	{
		*orig_in = copy_stream(0);
		if (*orig_in == -1)
			return(-1);
	}
	if (cmd->out)
	{
		*orig_out = copy_stream(1);
		if (*orig_out == -1)
		{
			if (*orig_in != -1)
				close(*orig_in);
			return(-1);
		}
	}
	if (handle_redirs(data, cmd) == -1)
	{
		restore_streams(data, *orig_in, *orig_out);
		return (-1);
	}
	return (0);
}

int	process_cmd(t_data *data, t_command *cmd)
{
	// int	builtin_status;
	int	orig_stdin;
	int	orig_stdout;
	int	is_redir;
	int exit_status;

	exit_status = 0;
	is_redir = 0;
	if (cmd->redirections)
	{
		is_redir = 1;
		if (redirect_io(data, cmd, &orig_stdin, &orig_stdout) == -1)
		{
			data->status = 1;
			return (1);
		}
	}
	if (cmd->args)
	{
		exit_status = run_bltin(data, cmd);
		if (exit_status == -1)
			exit_status = run_external(data, cmd);
	}
	if (is_redir)
		restore_streams(data, orig_stdin, orig_stdout);
	return (exit_status);
}
