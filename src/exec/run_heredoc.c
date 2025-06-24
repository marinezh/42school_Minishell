#include "minishell.h"

/* Heredoc implementation approach:
 * 1. Create a temporary file with unique name in /tmp
 * 2. Open for both reading and writing
 * 3. Immediately unlink so file disappears from filesystem
 * 4. Collect user input until delimiter is found
 * 5. Close write fd, store read fd in command node for later use
 */

char	*create_new_name(void)
{
	static int	counter = 0;
	char		temp[1];
	uintptr_t	addr_ptr;
	char		*heredoc_num;
	char		*heredoc_name;

	addr_ptr = (uintptr_t)&temp + counter++;
	heredoc_num = ft_itoa((int)addr_ptr);
	heredoc_name = ft_strjoin("/tmp/heredoc_", heredoc_num);
	free(heredoc_num);
	if (!heredoc_name)
		return (NULL);
	return (heredoc_name);
}

void	print_eof_warning(t_files *node, int line_num)
{
	char	full_msg[256];
	char	*number;

	number = ft_itoa(line_num);
	if (!number)
		return ;
	ft_strlcpy(full_msg, "minishell: warning: here-document at line ",
		sizeof(full_msg));
	ft_strlcat(full_msg, number, sizeof(full_msg));
	ft_strlcat(full_msg, " delimited by end-of-file (wanted `",
		sizeof(full_msg));
	ft_strlcat(full_msg, node->name, sizeof(full_msg));
	ft_strlcat(full_msg, "')\n", sizeof(full_msg));
	ft_putstr_fd(full_msg, 2);
	free(number);
}
int	handle_expansion(t_files *node, char **input, t_data *data)
{
	char	*expanded;

	if (!node || !input || !*input || !data)
		return (-1);
	if (node->to_expand)
	{
		expanded = expand_heredoc_line(*input, data);
		if (!expanded)
			return (-1);
		free(*input);
		*input = expanded;
	}
	return (0);
}
void cleanup_and_close(char *input, int fd1, int fd2)
{
	if (input)
		free(input);
	if (fd1 >= 0)
		close (fd1);
	if (fd2 >= 0)
		close (fd2);
}
int	write_line_to_file(char *input, int fd_write)
{
	char	*input_nl;

	input_nl = ft_strjoin(input, "\n");
	if (!input_nl)
		return (-1);
	if (write(fd_write, input_nl, ft_strlen(input_nl)) == -1)
	{
		free(input_nl);
		perror("write");
		return (-1);
	}
	free(input_nl);
	return (0);
}

int	is_delimiter(char *input, char *delimiter)
{
	return (ft_strcmp(input, delimiter) == 0);
}

int	collect_input(t_files *node, int fd_read, int fd_write, t_data *data)
{
	char	*input;
	int		line_count;

	line_count = 1;
	while (1)
	{
		input = readline("> ");
		if (!input)
		{
			print_eof_warning(node, line_count);
			return (0);
		}
		if (is_delimiter(input, node->name))
		{
			free(input);
			break ;
		}
		if (handle_expansion(node, &input, data) == -1 ||
			write_line_to_file(input, fd_write) == -1)
		{
			cleanup_and_close(input, fd_read, fd_write);
			return (-1);
		}
		free(input);
		line_count++;
	}
	return (0);
}

void	handle_heredoc_collection(t_files *cur_node, t_command *cmd, int fd_read, int fd_write, t_data *data)
{
	int	exit_status;

	exit_status = 0;
	reset_signals_to_default();
	if (collect_input(cur_node, fd_read, fd_write, data) == -1)
		exit_status = 1;
	cleanup_process_data(data);
	close(fd_read);
	close(fd_write);
	free_command_list(cmd);
	exit(exit_status);
}

int	collect_heredoc_process(t_files *cur_node, t_command *cmd, int fd_read, int fd_write, t_data *data)
{
	pid_t	pid;
	int		exit_code;

	exit_code = 0;
	pid = create_process();
	if (pid == -1)
	{
		close(fd_read);
		close(fd_write);
		return (ERR_GENERIC);
	}
	if (pid == 0)
		handle_heredoc_collection(cur_node, cmd, fd_read, fd_write, data);
	else
		exit_code = handle_parent_process(pid);
	return (exit_code);
}

int	setup_heredoc_fds(int *fd_write, int *fd_read)
{
	char	*heredoc_name;

	heredoc_name = create_new_name();
	if (!heredoc_name)
		return (-1);
	*fd_write = open(heredoc_name, O_WRONLY | O_CREAT | O_TRUNC, 0600);
	if (*fd_write == -1)
	{
		perror("open");
		free(heredoc_name);
		return (-1);
	}
	*fd_read = open(heredoc_name, O_RDONLY);
	unlink(heredoc_name);
	free(heredoc_name);
	if (*fd_read == -1)
	{
		perror("open");
		close(*fd_write);
		return (-1);
	}
	return (0);
}

int	process_heredoc(t_data *data, t_command *cmd, t_files *cur_node)
{
	int					fd_write;
	int					fd_read;

	if (setup_heredoc_fds(&fd_write, &fd_read) == -1)
		return (-1);
	data->status = collect_heredoc_process(cur_node, cmd, fd_read, fd_write, data);
	if (data->status == 130)
	{
		close(fd_read);
		close(fd_write);
		return (-1);
	}
	close(fd_write);
	cur_node->fd = fd_read;
	return (0);
}
