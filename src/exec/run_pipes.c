#include "minishell.h"

void	close_unused_heredoc_fds(t_command *cmd, t_command *cur_cmd)
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

int	run_pipes(t_data *data, t_command *cmd, int cmd_count)
{
	int input_pipe[2] = {-1, -1};
	int cur_pipe[2] = {-1, -1};
	// pid_t		pid;
	pid_t		pids[cmd_count];
	int			i;
	int			exit_code;
	t_command	*cur_cmd;
	int			status;
	

	cur_cmd = cmd;
	i = 0;
	while (cur_cmd && i < cmd_count)
	{
		if (i < cmd_count - 1)
		{
			if (pipe(cur_pipe) == -1)
			{
				ft_putstr_fd("minishell: pipe: Too many open files\n",
					STDERR_FILENO);
				if (input_pipe[0] != -1)
					close(input_pipe[0]);
				return (1);
			}
		}
		pids[i] = create_process();
		if (pids[i] < 0)
		{
			ft_putstr_fd("minishell: fork: Cannot allocate memory\n",
				STDERR_FILENO);
			if (input_pipe[0] != -1)
				close(input_pipe[0]);
			if (cur_pipe[0] != -1) 
			{ 
				close(cur_pipe[0]); 
				close(cur_pipe[1]); 
			}
			return (1);
		}
		if (pids[i] == 0)
		{
			reset_signals_to_default();
			close_unused_heredoc_fds(cmd, cur_cmd);
			// redirect out/in
			if (i > 0)
			{
				if (dup2(input_pipe[0], STDIN_FILENO) == -1)
				{
					perror("dup2");
					cleanup_process_data(data);
					free_command_list(cmd);
					exit(1);
				}
				close(input_pipe[0]);
				// close(input_pipe[1]);
			}
			if (i < cmd_count - 1)
			{
				if (dup2(cur_pipe[1], STDOUT_FILENO) == -1)
				{
					perror("dup2");
					close(cur_pipe[0]);
					close(cur_pipe[1]);
					cleanup_process_data(data);
					free_command_list(cmd);
					exit(1);
				}
				close(cur_pipe[1]);
				close(cur_pipe[0]);
			}
			exit_code = process_cmd(data, cur_cmd);
			cleanup_process_data(data);
			free_command_list(cmd);
			exit(exit_code);
		}
		if (i > 0) 
		{
            close(input_pipe[0]);
			if (input_pipe[1] != -1)  // This check is important!
				close(input_pipe[1]);
        }
		if (i < cmd_count - 1) 
		{
			close(cur_pipe[1]);  // Close write end we just passed to child
			input_pipe[0] = cur_pipe[0];  // Save read end for next iteration
			input_pipe[1] = -1; 
        }
		cur_cmd = cur_cmd->next; 
		i++;
	}
	i = 0;
	while (i < cmd_count - 1)
		waitpid(pids[i++], NULL, 0);
	status = handle_parent_process(pids[cmd_count - 1]);
	return (status);
}


// int	run_pipes(t_data *data, t_command *cmd, int cmd_count)
// {
// 	pid_t		*pids;
// 	int			**fds;
// 	int			i;
// 	int			j;
// 	int			exit_code;
// 	t_command	*cur_cmd;
// 	int			final_status;

// 	// created pids for processes == cmd_count
// 	pids = ft_calloc(cmd_count, sizeof(pid_t));
// 	if (!pids)
// 	{
// 		perror("calloc");
// 		return (1);
// 	}
// 	// create array for fds{0,1}, number of pipes
// 	fds = ft_calloc(cmd_count - 1, sizeof(int *));
// 	if (!fds)
// 	{
// 		free(pids);
// 		return (1);
// 	}
// 	i = 0;
// 	while (i < cmd_count - 1)
// 	{
// 		fds[i] = ft_calloc(2, sizeof(int));
// 		if (!fds[i])
// 		{
// 			perror("calloc");
// 			free_fds(fds, i);
// 			free(pids);
// 			return (1);
// 		}
// 		i++;
// 	}
// 	i = 0;
// 	// create pipes and connect with fds
// 	while (i < (cmd_count - 1))
// 	{
// 		if (pipe(fds[i]) == -1)
// 		{
// 			ft_putstr_fd("minishell: pipe: Too many open files\n",
// 				STDERR_FILENO);
// 			j = 0;
// 			while (j < cmd_count - 1)
// 			{
// 				close(fds[j][0]);
// 				close(fds[j][1]);
// 				j++;
// 			}
// 			free_fds(fds, i);
// 			free(pids);
// 			return (1);
// 		}
// 		i++;
// 	}
// 	i = 0;
// 	// create processes
// 	cur_cmd = cmd;
// 	while (i < cmd_count)
// 	{
// 		pids[i] = create_process();
// 		if (pids[i] < 0)
// 		{
// 			ft_putstr_fd("minishell: fork: Cannot allocate memory\n",
// 				STDERR_FILENO);
// 			free_fds(fds, cmd_count - 2);
// 			free(pids);
// 			return (1);
// 		}
// 		if (pids[i] == 0)
// 		{
// 			reset_signals_to_default();
// 			close_unused_heredoc_fds(cmd, cur_cmd);
// 			// redirect out/in
// 			if (i != 0)
// 			{
// 				if (dup2(fds[i - 1][0], STDIN_FILENO) == -1)
// 				{
// 					perror("dup2");
// 					cleanup_process_data(data);
// 					free(pids);
// 					free_fds(fds, cmd_count - 2);
// 					free_command_list(cmd);
// 					exit(1);
// 				}
// 			}

// 			if (i != cmd_count - 1)
// 			{
// 				if (dup2(fds[i][1], STDOUT_FILENO) == -1)
// 				{
// 					perror("dup2");
// 					cleanup_process_data(data);
// 					free(pids);
// 					free_fds(fds, cmd_count - 2);
// 					free_command_list(cmd);
// 					exit(1);
// 				}
// 			}
// 			j = 0;
// 			while (j < cmd_count - 1)
// 			{
// 				close(fds[j][0]);
// 				close(fds[j][1]);
// 				j++;
// 			}
// 			exit_code = process_cmd(data, cur_cmd);
// 			cleanup_process_data(data);
// 			free(pids);
// 			free_fds(fds, cmd_count - 2);
// 			free_command_list(cmd);
// 			exit(exit_code);
// 		}
// 		cur_cmd = cur_cmd->next;
// 		i++;
// 	}
// 	i = 0;
// 	while (i < cmd_count - 1)
// 	{
// 		close(fds[i][0]);
// 		close(fds[i][1]);
// 		i++;
// 	}
// 	i = 0;
// 	while (i < cmd_count - 1)
// 	{
// 		handle_parent_process(pids[i]);
// 		i++;
// 	}
// 	final_status = handle_parent_process(pids[cmd_count - 1]);
// 	free(pids);
// 	free_fds(fds, cmd_count - 2);
// 	return (final_status);
// }

// each process has its own fd table which is a copy of parent fd table
// fd in those tables reference the same objects for read end and write end