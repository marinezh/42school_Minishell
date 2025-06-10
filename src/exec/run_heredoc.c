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
	return(heredoc_name);
}
int	collect_input(t_files *node, int fd_read, int fd_write)
{
	char	*input;
	char	*input_nl;

	while (1)
	{
		input = readline("> ");
		if (!input)
		{
			ft_putstr_fd("minishell: warning: ", 2);
			ft_putstr_fd("here-document delimited by end-of-file (wanted ", 2);
			printf("`%s')\n", node->name);
			//TODO: check cntl + D - cause "dup2: Bad file descriptor" and what is wanted as delimeted
			close(fd_write);
			close(fd_read);
			return (-1);
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
			return(-1);
		}
		free(input_nl);
		free(input);
	}
	return (0);
}

int	process_heredoc(t_data *data, t_files *cur_node)
{
	int		fd_write;
	int		fd_read;
	char	*heredoc_name;

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
	if (collect_input(cur_node, fd_read, fd_write) == -1)
	{
		close(fd_read);
		close(fd_write);
		return (-1);
	}
	close(fd_write);
	cur_node->fd = fd_read;
	data->status = 0;
	return(0);
}
