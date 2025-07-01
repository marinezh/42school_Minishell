#include "minishell.h"

int	count_commands(t_command *head)
{
	t_command	*cur;
	int			count;

	cur = head;
	count = 0;
	while(cur)
	{
		count++;
		cur = cur->next;
	}
	return(count);
}

int	has_heredoc(t_data *data, t_command *cmd)
{
	t_command	*cur_cmd;
	t_files		*cur_redir;
	int			count;

	count = 0;
	cur_cmd = cmd;
	while (cur_cmd)
	{
		cur_redir = cur_cmd->redirections;
		while (cur_redir)
		{
			if (cur_redir->type == HEREDOC)
			{
				count++;
				if (count > 16)
				{
					ft_putstr_fd("minishell: maximum here-document count exceeded\n", 2);
					data->exit_f = 1;
					return (-1);
				}
			}
			cur_redir = cur_redir->next;
		}
		cur_cmd = cur_cmd->next;
	}
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
	if (!cmd)
	{
		//data->status = ERR_GENERIC;
		data->status = 0;
		return ;
	}
	if (!cmd->redirections && (!cmd->args || !cmd->args[0]))
	{
		data->status = 0;
		return ;
	}
	if (has_heredoc(data, cmd) == -1)
		return ;
	cmd_count = count_commands(cmd);
	if (cmd_count > 1)
		status = run_pipes(data, cmd, cmd_count);
	else
		status = process_cmd(data, cmd);
	data->status = status;
}
//**command not found -> status changes to 127, but not exit bash

//CHEcK code for this commands (command->status)
/*
bash-3.2$ cat <s1 <z1
bash: z1: Permission denied
bash-3.2$ echo $?
1
bash-3.2$ cat <s1 <w1  <z1
bash: w1: No such file or directory
bash-3.2$ echo $?
1
*/
// CHECK run cat <f1 empty file with valgrind