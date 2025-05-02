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
//print only variables with value? or all?