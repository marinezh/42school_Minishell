/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_pipes_1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikozhina <ikozhina@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 10:37:04 by ikozhina          #+#    #+#             */
/*   Updated: 2025/07/12 11:02:49 by ikozhina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	setup_pipe(t_pipe *pdata)
{
	if (pipe(pdata->cur_pipe) == -1)
	{
		ft_putstr_fd("minishell: pipe: Too many open files\n", STDERR_FILENO);
		if (pdata->in_pipe[0] != -1)
			close(pdata->in_pipe[0]);
		return (1);
	}
	return (0);
}

static int	handle_fork_error(t_pipe pdata)
{
	ft_putstr_fd("minishell: fork: Cannot allocate memory\n", STDERR_FILENO);
	if (pdata.in_pipe[0] != -1)
		close(pdata.in_pipe[0]);
	if (pdata.cur_pipe[0] != -1)
	{
		close(pdata.cur_pipe[0]);
		close(pdata.cur_pipe[1]);
	}
	return (1);
}

static void	handle_parent_pipe(t_pipe *pdata, int i, int count)
{
	if (i > 0)
	{
		close(pdata->in_pipe[0]);
		if (pdata->in_pipe[1] != -1)
			close(pdata->in_pipe[1]);
	}
	if (i < count - 1)
	{
		close(pdata->cur_pipe[1]);
		pdata->in_pipe[0] = pdata->cur_pipe[0];
		pdata->in_pipe[1] = -1;
	}
}

static int	wait_for_processes(pid_t *pids, int cmd_count)
{
	int		wcount;
	int		wstatus;
	int		exit_code;
	pid_t	pid;

	wcount = cmd_count;
	while (wcount--)
	{
		pid = waitpid(0, &wstatus, 0);
		if (pid != -1)
		{
			if (pid == pids[cmd_count - 1])
				exit_code = get_pipe_exit_code(wstatus);
		}
		else
		{
			perror("waitpid");
			exit_code = ERR_GENERIC;
			break ;
		}
	}
	return (exit_code);
}

int	run_pipes(t_data *data, t_command *cmd, int cmd_count)
{
	t_pipe	pdata;
	pid_t	*pids;
	int		i;

	pids = data->pids;
	init_pipe_data(&pdata, cmd, cmd_count);
	i = 0;
	while (pdata.cur_cmd && i < cmd_count)
	{
		if (i < cmd_count - 1)
			setup_pipe(&pdata);
		pids[i] = create_process();
		if (pids[i] < 0)
			return (handle_fork_error(pdata));
		else if (pids[i] == 0)
			handle_child_pipe(data, cmd, pdata, i);
		else
			handle_parent_pipe(&pdata, i, cmd_count);
		pdata.cur_cmd = pdata.cur_cmd->next;
		i++;
	}
	return (wait_for_processes(pids, cmd_count));
}
