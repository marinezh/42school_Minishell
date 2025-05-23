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

int	check_redirections(t_command *cmd)
{
	t_files	*cur;

	if (cmd->out)
		return(1);
	cur = cmd->in;
	while (cur)
	{
		if (cur->type == REDIR_IN)
			return (1);
		cur = cur->next;
	}
	return(0);
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
	int	status;

	status = 0;
	if (redirect_stream(data, orig_stdin, 0) == -1)
	{
		status = -1;
		perror("restore stdin");
	}
	if (status != -1 && (redirect_stream(data, orig_stdout, 1) == -1))
	{
		perror("restore stdout");
		status = -1;
	}
	close(orig_stdin);
	close(orig_stdout);
}

int	redirect_io(t_data *data, t_command *cmd, int *orig_in, int *orig_out)
{
	int	redir_status;

	*orig_in = copy_stream(0);
	if (*orig_in == -1)
		return(-1);
	*orig_out = copy_stream(1);
	if (*orig_out == -1)
	{
		close(*orig_in);
		return(-1);
	}
	redir_status = handle_redirs(data, cmd);
	if (redir_status == -1)
	{
		restore_streams(data, *orig_in, *orig_out);
		return (-1);
	}
	return (0);
}

int	execute(t_data *data, t_command *cmd)
{
	int	builtin_status;
	int	orig_stdin;
	int	orig_stdout;
	int	is_redir;

	is_redir = check_redirections(cmd);
	if (!cmd || !cmd->args || !cmd->args[0] || cmd->args[0][0] == '\0')
	{
		data->status = ERR_GENERIC;
		return (-1);
	}
	if (is_redir && (redirect_io(data, cmd, &orig_stdin, &orig_stdout) == -1))
		return (-1);
	builtin_status = run_bltin(data, cmd);
	if (builtin_status != -1)
	{
		if (is_redir)
			restore_streams(data, orig_stdin, orig_stdout);
		return (builtin_status);
	}
	run_external(data, cmd);
	if (is_redir)
		restore_streams(data, orig_stdin, orig_stdout);
	return (0);
}
//**command not found -> status changes to 127, but not exit bash

//CHEcK code for this commands (command->status)
/*
bash-3.2$ cat <s1 <z1
bash: z1: Permission denied
bash-3.2$ echo $?
1
bash-3.2$ cat <s1 <w1  <z1
bash: w1: No such file or directory
bash-3.2$ echo $?
1
*/
// CHECK run cat <f1 empty file with valgrind