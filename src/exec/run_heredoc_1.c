/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_heredoc_1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikozhina <ikozhina@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 10:36:05 by ikozhina          #+#    #+#             */
/*   Updated: 2025/07/14 15:39:24 by ikozhina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Heredoc implementation approach:
 * 1. Create a temporary file with unique name in /tmp
 * 2. Open for both reading and writing
 * 3. Immediately unlink so file disappears from filesystem
 * 4. Collect user input until delimiter is found
 * 5. Close write fd, store read fd in command node for later use
 */

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

static char	*create_new_name(void)
{
	static int	counter;
	char		temp[1];
	uintptr_t	addr_ptr;
	char		*heredoc_num;
	char		*heredoc_name;

	addr_ptr = ((uintptr_t) & temp) + counter++;
	heredoc_num = ft_itoa((int)addr_ptr);
	if (!heredoc_num)
		return (NULL);
	heredoc_name = ft_strjoin("/tmp/heredoc_", heredoc_num);
	free(heredoc_num);
	if (!heredoc_name)
		return (NULL);
	return (heredoc_name);
}

static int	run_heredoc(t_data *data, t_command *cmd, t_files *node, int *fds)
{
	pid_t	pid;
	int		exit_code;

	exit_code = 0;
	pid = create_process();
	if (pid == -1)
	{
		close(fds[0]);
		close(fds[1]);
		return (ERR_GENERIC);
	}
	if (pid == 0)
		heredoc_child(node, cmd, fds, data);
	else
		exit_code = handle_heredoc_parent(pid);
	return (exit_code);
}

static int	setup_heredoc_fds(int *fds)
{
	char	*heredoc_name;

	heredoc_name = create_new_name();
	if (!heredoc_name)
		return (-1);
	fds[1] = open(heredoc_name, O_WRONLY | O_CREAT | O_TRUNC, 0600);
	if (fds[1] == -1)
	{
		perror("open");
		free(heredoc_name);
		return (-1);
	}
	fds[0] = open(heredoc_name, O_RDONLY);
	unlink(heredoc_name);
	free(heredoc_name);
	if (fds[0] == -1)
	{
		perror("open");
		close(fds[1]);
		return (-1);
	}
	return (0);
}

int	process_heredoc(t_data *data, t_command *cmd, t_files *node)
{
	int	fds[2];

	if (setup_heredoc_fds(fds) == -1)
		return (-1);
	data->status = run_heredoc(data, cmd, node, fds);
	if (data->status != 0)
	{
		close(fds[0]);
		close(fds[1]);
		return (-1);
	}
	close(fds[1]);
	node->fd = fds[0];
	return (0);
}
