#include "minishell.h"

int	execute(t_data *data, t_command *cmd)
{
	int	builtin_status;
	// int	external_cmd_status;

	if (!cmd || !cmd->args || !cmd->args[0] || cmd->args[0][0] == '\0')
	{
		data->status = ERR_GENERIC;
		return (-1);
	}
	// if (cmd_list_size(cmd) == 1)
	// {
	builtin_status = run_bltin(data, cmd);
	if (builtin_status != -1)
		return (builtin_status);
	// external_cmd_status =
	run_external(data, cmd);
	return (0);
}
//**command not found -> status changes to 127, but not exit bash
