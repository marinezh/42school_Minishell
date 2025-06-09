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
	int	redir_status;

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
	redir_status = handle_redirs(data, cmd);
	if (redir_status == -1)
	{
		restore_streams(data, *orig_in, *orig_out);
		return (-1);
	}
	return (0);
}

void	process_cmd(t_data *data, t_command *cmd)
{
	int	builtin_status;
	int	orig_stdin;
	int	orig_stdout;
	int	is_redir;

	is_redir = 0;
	if (cmd->in || cmd->out)
	{
		is_redir = 1;
		if (redirect_io(data, cmd, &orig_stdin, &orig_stdout) == -1)
		{
			data->status = 1;
			return ;
		}
	}
	if (cmd->args)
	{
		builtin_status = run_bltin(data, cmd);
		if (builtin_status == -1)
			run_external(data, cmd);
	}
	if (is_redir)
		restore_streams(data, orig_stdin, orig_stdout);
}
int	count_commands(t_command *head)
{
	t_command	*cur;
	int			count;

	cur = head;
	count = 0;
	while(cur)
	{
		count++;
		cur = cur->next;
	}
	return(count);
}

int	has_heredoc(t_data *data, t_command *cmd)
{
	t_command	*cur_cmd;
	t_files		*cur_in;
	int			count;

	count = 0;
	cur_cmd = cmd;
	while (cur_cmd)
	{
		cur_in = cur_cmd->in;
		while (cur_in)
		{
			if (cur_in->type == HEREDOC)
			{
				count++;
				if (count > 16)
				{
					ft_putstr_fd("minishell: maximum here-document count exceeded\n", 2);
					data->exit_f = 1;
					return (-1);
				}
			}
			cur_in = cur_in->next;
		}
		cur_cmd = cur_cmd->next;
	}
	printf("heredoc count - %d\n", count);
	cur_cmd = cmd;
	while (cur_cmd)
	{
		cur_in = cur_cmd->in;
		while (cur_in)
		{
			if (cur_in->type == HEREDOC)
			{
				if (process_heredoc(data, cur_in) == -1)
					return (-1);
			}
			cur_in = cur_in->next;
		}
		cur_cmd = cur_cmd->next;
	}
	return (0);
}

void	execute(t_data *data, t_command *cmd)
{
	int	cmd_count;

	if (!cmd)
	{
		data->status = ERR_GENERIC;
		return ;
	}
	if (!cmd->in && !cmd->out)
	{
		if (!cmd->args || !cmd->args[0] || cmd->args[0][0] == '\0')
		{
			data->status = 0;
			return ;
		}
	}
	if (has_heredoc(data, cmd) == -1)
	{
		data->status = ERR_GENERIC;
		return ;
	}
	cmd_count = count_commands(cmd);
	if (cmd_count > 1)
		run_pipes(data, cmd, cmd_count);
	else
		process_cmd(data, cmd);
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