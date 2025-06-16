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
			handle_error_arg(data, file, MSG_NO_FILE, ERR_GENERIC);
		else if (errno == EACCES)
			handle_error_arg(data, file, MSG_NO_PERM, ERR_GENERIC);
		else
			perror("open");
		data->status = 1;
		return (-1);
	}
	if (redirect_stream(data, fd, 0) == -1)
	{
		close(fd);
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
				handle_error_arg(data, file, MSG_NO_PERM, ERR_GENERIC);
			else
				perror("open");
			data->status = 1;
			return (-1);
		}
		if (redirect_stream(data, fd, 1) == -1)
		{
			close(fd);
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
				handle_error_arg(data, file, MSG_NO_PERM, ERR_GENERIC);
			else
				perror("open");
			data->status = 1;
			return (-1);
		}
		if (redirect_stream(data, fd, 1) == -1)
		{
			close(fd);
			return (-1);
		}
		close(fd);
	}
	data->status = 0;
	return (data->status);
}

int	handle_redirs(t_data *data, t_command *cmd)
{
	t_files *cur_redir;
	int res;

	res = 0;
	cur_redir = cmd->redirections;
	while (cur_redir)
	{
		if (cur_redir->type == HEREDOC)
		{
			res = redirect_stream(data, cur_redir->fd, 0);
			close(cur_redir->fd);
			cur_redir->fd = -1;
		}
		else if (cur_redir->type == REDIR_IN)
			res = process_redir_in(data, cur_redir);
		else if (cur_redir->type == REDIR_OUT || cur_redir->type == REDIR_APPEND)
			res = process_redir_out(data, cur_redir);
		if (res == -1)
			break ;
		cur_redir = cur_redir->next;
	}
	return (res);
}
