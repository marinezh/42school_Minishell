#include"minishell.h"

int ft_env(t_data *data, t_command *cmd)
{
	int	i;

	i = 0;
    if (cmd->args[1])
    {
        ft_putstr_fd("minishell: env: ", STDERR_FILENO);
        ft_putstr_fd("options or arguments are not supported\n", STDERR_FILENO);
        return (ERROR_GENERIC);
    }
	if (data->envp_f)
	{
		update_envp_array(data, data->envp_list);
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
//print only variables with value, don't print empty variables
//if anything is typied after env - no other parameters are allowed after env
//order - printed as they are created!