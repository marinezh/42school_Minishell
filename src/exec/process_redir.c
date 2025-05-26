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
// TODO: free after readline (allocate memory in heap)
// then free after join
// TODO: close fd

int	collect_heredoc_input(t_data *data, t_files *cur_node)
{
	static int heredoc_counter = 0;
	char	*heredoc_num;
	char	*input;
	int		fd;
	char	*input_nl;
	char	*temp_name;
	// char	*line;

	heredoc_num = ft_itoa(heredoc_counter++);
	if (!heredoc_num)
		return (-1);
	temp_name = ft_strjoin("heredoc_", heredoc_num);
	free(heredoc_num);
	if (!temp_name)
		return (-1);
	fd = open(temp_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		perror("open");
		free(temp_name);
		return (-1);
	}
	while (1)
	{
		input = readline("> ");
		if (!input)
		{
			close(fd);
			unlink(temp_name);
			free(temp_name);
			return (-1);
		}
		if (ft_strcmp(input, cur_node->name) == 0)
		{
			free(input);
			break ;
		}
		input_nl = ft_strjoin(input, "\n");
		if (!input_nl)
		{
			free(input);
			close(fd);
			unlink(temp_name);
			free(temp_name);
			return (-1);
		}
		write(fd, input_nl, ft_strlen(input_nl));
		free(input_nl);
		free(input);
	}
	close(fd);
	fd = open(temp_name, O_RDONLY);
	if (fd == -1)
	{
		perror("open");
		unlink(temp_name);
		free(temp_name);
		return (-1);
	}
	unlink(temp_name);
	free(temp_name);
	cur_node->fd = fd;
	data->status = 0;
	return(data->status);

	// while (1)
	// {
	// 	line = get_next_line(fd_read);
	// 	if (!line)
	// 		break;
	// 	printf("%s", line);
	// }
	// close(fd_read);
}

int	handle_redirs(t_data *data, t_command *cmd)
{
	t_files	*cur_in;
	t_files *cur_out;
	int res;

	res = 0;
	cur_in = cmd->in;
	cur_out = cmd->out;
	while (cur_in)
	{
		if (cur_in->type == HEREDOC)
		{
			res = collect_heredoc_input(data, cur_in);
			if (res == -1)
				break;
		}
		cur_in = cur_in->next;
	}
	cur_in = cmd->in;
	while (cur_in)
	{
		if (cur_in->type == HEREDOC)
		{
			res = redirect_stream(data, cur_in->fd, 0);
			close(cur_in->fd);
		}
		else
			res = process_redir_in(data, cur_in);
		if (res == -1)
			break;
		cur_in = cur_in->next;
	}
	if (res == -1)
		return (res);
	while (cur_out)
	{
		res = process_redir_out(data, cur_out);
		if (res == -1)
			break;
		cur_out = cur_out->next;
	}
	return (res);
}
