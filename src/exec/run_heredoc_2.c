/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_heredoc_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikozhina <ikozhina@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 10:36:41 by ikozhina          #+#    #+#             */
/*   Updated: 2025/07/12 10:36:43 by ikozhina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	handle_exp(t_files *node, char **input, t_data *data)
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

static int	write_line_to_file(char *input, int fd_write)
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

static int	handle_line(t_data *data, char *input, t_files *node, int *fds)
{
	if (ft_strcmp(input, node->name) == 0)
	{
		free(input);
		return (1);
	}
	if (handle_exp(node, &input, data) == -1 || write_line_to_file(input,
			fds[1]) == -1)
	{
		if (input)
			free(input);
		if (fds[1] >= 0)
			close(fds[1]);
		return (-1);
	}
	free(input);
	return (0);
}

static int	collect_input(t_files *node, int *fds, t_data *data)
{
	char	*input;
	int		line_count;
	int		res;

	line_count = 1;
	while (1)
	{
		input = readline("> ");
		if (g_sig_received)
		{
			free(input);
			return (-1);
		}
		if (!input)
		{
			print_eof_warning(node, line_count);
			return (0);
		}
		res = handle_line(data, input, node, fds);
		if (res == 1)
			return (0);
		else if (res == -1)
			return (-1);
		line_count++;
	}
}

void	heredoc_child(t_files *node, t_command *cmd, int *fds, t_data *data)
{
	int	exit_status;

	exit_status = 0;
	set_heredoc_signals();
	rl_event_hook = heredoc_signal_hook;
	close(fds[0]);
	if (collect_input(node, fds, data) == -1)
	{
		if (g_sig_received == SIGINT)
		{
			g_sig_received = 0;
			exit_status = 130;
		}
		else
			exit_status = 1;
	}
	cleanup_process_data(data);
	close(fds[1]);
	free_command_list(cmd);
	exit(exit_status);
}
