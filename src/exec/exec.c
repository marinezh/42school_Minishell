#include "minishell.h"

int	process_redir_in(t_data *data, t_files *redir_in)
{
	int		fd;
	char	*file;

	file = redir_in->name;
	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		if (errno == ENOENT)
			handle_error_arg(data, file, MSG_NO_FILE, ERR_CMD_NOT_FOUND);
		else if (errno == EACCES)
			handle_error_arg(data, file, MSG_NO_PERM, ERR_CMD_NOT_FOUND);
		else
			perror("open");
		data->status = 1;
		return (-1);
	}
	if (dup2(fd, 0) == -1)
	{
		perror("dup2");
		close(fd);
		data->status = 1;
		return (-1);
	}
	close(fd);
	data->status = 0;
	return (data->status);
}

int	process_redir_out(t_data *data, t_files *redir_out)
{
	int		type;
	int		fd;
	char	*file;

	type = redir_out->type;
	file = redir_out->name;
	if (type == REDIR_OUT)
	{
		fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd == -1)
		{
			if (errno == EACCES)
				handle_error_arg(data, file, MSG_NO_PERM, ERR_CMD_NOT_FOUND);
			else
				perror("open");
			data->status = 1;
			return (-1);
		}
		if (dup2(fd, 1) == -1)
		{
			perror("dup2");
			close(fd);
			data->status = 1;
			return (-1);
		}
		close(fd);
	}
	else if (type == REDIR_APPEND)
	{
		fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (fd == -1)
		{
			if (errno == EACCES)
				handle_error_arg(data, file, MSG_NO_PERM, ERR_CMD_NOT_FOUND);
			else
				perror("open");
			data->status = 1;
			return (-1);
		}
		if (dup2(fd, 1) == -1)
		{
			perror("dup2");
			close(fd);
			data->status = 1;
			return (-1);
		}
		close(fd);
	}
	data->status = 0;
	return (data->status);
}

int	handle_redirs(t_data *data, t_command *cmd)
{
	t_files	*cur_in;
	t_files *cur_out;
	int res;

	res = 0;
	cur_in = cmd->in;
	cur_out = cmd->out;
	while (cur_in && cur_in->type != HEREDOC)
	{
		res = process_redir_in(data, cur_in);
		if (res == -1)
			break;
		cur_in = cur_in->next;
	}
	if (res == -1)
		return (res);
	else 
	{
		while (cur_out)
		{
			res = process_redir_out(data, cur_out);
			if (res == -1)
				break;
			cur_out = cur_out->next;
		}
	}
	return (res);
}

int	execute(t_data *data, t_command *cmd)
{
	int	builtin_status;
	int redir_status;
	int orig_stdin;
	int orig_stdout;

	if (!cmd || !cmd->args || !cmd->args[0] || cmd->args[0][0] == '\0')
	{
		data->status = ERR_GENERIC;
		return (-1);
	}
	if (cmd->in || cmd->out)
	{
		orig_stdin = dup(0);
		if (orig_stdin == -1)
		{
			perror("dup");
			return(-1);
		}
		orig_stdout = dup(1);
		if (orig_stdout == -1)
		{
			perror("dup");
			return(-1);
		}
		redir_status = handle_redirs(data, cmd);
		if (redir_status == -1)
		{
			dup2(orig_stdin, 0);
			dup2(orig_stdout, 1);
			close(orig_stdin);
			close(orig_stdout);
			return (-1);
		}
	}
	// execute command func
	builtin_status = run_bltin(data, cmd);
	if (builtin_status != -1)
		return (builtin_status);
	else
		run_external(data, cmd);
	dup2(orig_stdin, 0);
	dup2(orig_stdout, 1);
	close(orig_stdin);
	close(orig_stdout);
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
//CHECK run cat <f1 empty file with valgrind