#include"minishell.h"

int ft_env(t_data *data, t_command *cmd)
{
	int	i;

	i = 0;
    if (cmd->args[1])
    {
        print_error_msg("env", MSG_NO_OPTS_ARGS);
        return(ERR_GENERIC);
    }
	if (data->envp_f)
	{
		rebuild_envp_array(data, data->envp_list);
		data->envp_f = 0;
	}
	if (data->envp)
	{
		while (data->envp[i])
		{
			if (ft_strchr(data->envp[i], '='))
				printf("%s\n", data->envp[i]);
			i++;
		}
	}
	return(0);
}
