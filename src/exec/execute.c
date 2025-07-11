#include "minishell.h"

int	count_commands(t_command *head)
{
	t_command	*cur;
	int			count;

	cur = head;
	count = 0;
	while (cur)
	{
		count++;
		cur = cur->next;
	}
	return (count);
}

int	check_heredoc_limit(t_data *data, t_command *cmd)
{
	int			count;
	t_command	*cur_cmd;
	t_files		*cur_redir;

	count = 0;
	cur_cmd = cmd;
	while (cur_cmd)
	{
		cur_redir = cur_cmd->redirections;
		while (cur_redir)
		{
			if (cur_redir->type == HEREDOC && ++count > 16)
			{
				ft_putstr_fd("minishell: maximum here-document count exceeded\n",
					2);
				data->exit_f = 1;
				return (-1);
			}
			cur_redir = cur_redir->next;
		}
		cur_cmd = cur_cmd->next;
	}
	return (0);
}

int	has_heredoc(t_data *data, t_command *cmd)
{
	t_command	*cur_cmd;
	t_files		*cur_redir;

	if (check_heredoc_limit(data, cmd) == -1)
		return (-1);
	cur_cmd = cmd;
	while (cur_cmd)
	{
		cur_redir = cur_cmd->redirections;
		while (cur_redir)
		{
			if (cur_redir->type == HEREDOC)
			{
				if (process_heredoc(data, cmd, cur_redir) == -1)
					return (-1);
			}
			cur_redir = cur_redir->next;
		}
		cur_cmd = cur_cmd->next;
	}
	return (0);
}

void	execute(t_data *data, t_command *cmd)
{
	int	cmd_count;
	int	status;

	status = 0;
	if (!cmd || (!cmd->redirections && (!cmd->args || !cmd->args[0])))
	{
		data->status = 0;
		return ;
	}
	if (has_heredoc(data, cmd) == -1)
		return ;
	data->is_pipe = 0;
	safe_free_pointer((void **)&data->pids);
	cmd_count = count_commands(cmd);
	if (cmd_count > 1)
	{
		data->is_pipe = 1;
		data->pids = ft_calloc(cmd_count, sizeof(pid_t));
		if (!data->pids)
			return ;
		status = run_pipes(data, cmd, cmd_count);
	}
	else
		status = process_cmd(data, cmd);
	data->status = status;
}
