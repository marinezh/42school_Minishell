#include "minishell.h"

static int	remove_outer_quotes_from_string(t_qts_proc *p)
{
	if (!ft_strchr(p->str, '\'') && !ft_strchr(p->str, '"'))
		return (1);
	p->temp = malloc(ft_strlen(p->str) + 1); // CHECKED!!!!
	if (!p->temp)
		return (printf("malloc failed for [%s]\n", p->str), (0));
	p->i = 0;
	p->j = 0;
	p->in_quote = 0;
	while (p->str[p->i])
	{
		if ((p->str[p->i] == '\'' || p->str[p->i] == '"') && !p->in_quote)
			p->in_quote = p->str[p->i++];
		else if (p->str[p->i] == p->in_quote)
		{
			p->in_quote = 0;
			p->i++;
		}
		else
			p->temp[p->j++] = p->str[p->i++];
	}
	p->temp[p->j] = '\0';
	ft_strlcpy(p->str, p->temp, ft_strlen(p->str) + 1);
	free(p->temp);
	return (1);
}

static int	remove_quotes_from_files(t_files *files)
{
	t_files		*current;
	t_qts_proc	proc;

	current = files;
	while (current)
	{
		// if (current->type != HEREDOC)
		// {
		// 	proc.str = current->name;
		// 	if (!remove_outer_quotes_from_string(&proc))
		// 		return (0);
		// }
		proc.str = current->name;
			if (!remove_outer_quotes_from_string(&proc))
				return (0);
		current = current->next;
	}
	return (1);
}

int	remove_quotes_from_command_args(t_command *cmd, t_data *data)
{
	t_qts_proc	proc;
	int			i;

	while (cmd)
	{
		i = 0;
		while (cmd->args && cmd->args[i])
		{
			proc.str = cmd->args[i++];
			if (!remove_outer_quotes_from_string(&proc))
				return (data->status = ERR_GENERIC, 0);
		}
		if ((cmd->redirections && !remove_quotes_from_files(cmd->redirections))
			|| (cmd->in && !remove_quotes_from_files(cmd->in)) || (cmd->out
				&& !remove_quotes_from_files(cmd->out)))
			return (0);
		cmd = cmd->next;
	}
	return (1);
}
