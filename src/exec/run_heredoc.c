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

int	collect_input(t_files *node, int fd_read, int fd_write)
{
	char	*input;
	char	*input_nl;
	int		line_count;

	line_count = 1;
	while (1)
	{
		input = readline("> ");
		if (sig_received)
		{
			if (input)
				free(input);
			return (-1);
		}
		if (!input)
		{
			print_eof_warning(node, line_count);
			return (0);
		}
		if (ft_strcmp(input, node->name) == 0)
		{
			free(input);
			break ;
		}
		input_nl = ft_strjoin(input, "\n");
		if (!input_nl)
		{
			free(input);
			close(fd_write);
			close(fd_read);
			return (-1);
		}
		if (write(fd_write, input_nl, ft_strlen(input_nl)) == -1)
		{
			free(input_nl);
			free(input);
			close(fd_write);
			close(fd_read);
			perror("write");
			return (-1);
		}
		free(input_nl);
		free(input);
		line_count++;
	}
	return (0);
}

int	process_heredoc(t_data *data, t_files *cur_node)
{
	int					fd_write;
	int					fd_read;
	char				*heredoc_name;
	struct sigaction	old_int;
	struct sigaction	old_quit;

	sig_received = 0;
	sigaction(SIGINT, NULL, &old_int);
	sigaction(SIGQUIT, NULL, &old_quit);
	heredoc_name = create_new_name();
	fd_write = open(heredoc_name, O_WRONLY | O_CREAT | O_TRUNC, 0600);
	if (fd_write == -1)
	{
		perror("open");
		free(heredoc_name);
		return (-1);
	}
	fd_read = open(heredoc_name, O_RDONLY);
	unlink(heredoc_name);
	free(heredoc_name);
	if (fd_read == -1)
	{
		perror("open");
		close(fd_write);
		return (-1);
	}
	set_heredoc_signals();
	if (collect_input(cur_node, fd_read, fd_write) == -1)
	{
		close(fd_read);
		close(fd_write);
		sigaction(SIGINT, &old_int, NULL);
		sigaction(SIGQUIT, &old_quit, NULL);
		if (sig_received)
			data->status = 1;
		return (-1);
	}
	close(fd_write);
	cur_node->fd = fd_read;
	data->status = 0;
	sigaction(SIGINT, &old_int, NULL);
	sigaction(SIGQUIT, &old_quit, NULL);
	return (0);
}
