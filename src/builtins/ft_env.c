#include"minishell.h"

int ft_env(t_data *data, t_command *cmd)
{
    (void)cmd;
    int i;

    i = 0;
    if (data->envp_f)
    {
        update_envp_array(data, data->envp_list);
        data->envp_f = 0;
    }
    if (data->envp)
    {
        while (data->envp[i])
        {
            printf("%s\n", data->envp[i]);
            i++;
        }
    }
    return(0);
}
//print only variables with value, don't print empty variables
//if anything is typied after env - no other parameters are allowed after env only |
//order - printed as they are created!