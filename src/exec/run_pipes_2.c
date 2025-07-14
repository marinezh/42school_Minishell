/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_pipes_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikozhina <ikozhina@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 10:38:04 by ikozhina          #+#    #+#             */
/*   Updated: 2025/07/14 14:38:25 by ikozhina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_pipe_data(t_pipe *p_data, t_command *cmd, int cmd_count)
{
	p_data->cur_cmd = cmd;
	p_data->cmd_count = cmd_count;
	p_data->in_pipe[0] = -1;
	p_data->in_pipe[1] = -1;
	p_data->cur_pipe[0] = -1;
	p_data->cur_pipe[1] = -1;
}

static void	close_unused_heredoc_fds(t_command *cmd, t_command *cur_cmd)
{
	t_command	*iter_cmd;
	t_files		*cur_redir;

	iter_cmd = cmd;
	while (iter_cmd)
	{
		if (iter_cmd != cur_cmd)
		{
			cur_redir = iter_cmd->redirections;
			while (cur_redir)
			{
				if (cur_redir->type == HEREDOC && cur_redir->fd >= 0)
					close(cur_redir->fd);
				cur_redir = cur_redir->next;
			}
		}
		iter_cmd = iter_cmd->next;
	}
}

static int	setup_stdin_redir(t_pipe pdata, int i)
{
	if (i > 0)
	{
		if (dup2(pdata.in_pipe[0], STDIN_FILENO) == -1)
		{
			perror("dup2");
			return (1);
		}
		close(pdata.in_pipe[0]);
	}
	return (0);
}

static int	setup_stdout_redir(t_pipe pdata, int i)
{
	if (i < pdata.cmd_count - 1)
	{
		if (dup2(pdata.cur_pipe[1], STDOUT_FILENO) == -1)
		{
			perror("dup2");
			close(pdata.cur_pipe[0]);
			close(pdata.cur_pipe[1]);
			return (1);
		}
		close(pdata.cur_pipe[1]);
		close(pdata.cur_pipe[0]);
	}
	return (0);
}

void	handle_child_pipe(t_data *data, t_command *cmd, t_pipe pdata, int i)
{
	int	exit_code;

	close_unused_heredoc_fds(cmd, pdata.cur_cmd);
	if (setup_stdin_redir(pdata, i))
	{
		cleanup_data(data);
		free_command_list(cmd);
		exit(1);
	}
	if (setup_stdout_redir(pdata, i))
	{
		cleanup_data(data);
		free_command_list(cmd);
		exit(1);
	}
	exit_code = process_cmd(data, pdata.cur_cmd);
	cleanup_data(data);
	free_command_list(cmd);
	exit(exit_code);
}
