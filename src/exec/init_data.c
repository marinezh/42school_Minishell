#include"minishell.h"

void init_data(t_data *data)
{
    data->cmd_names[0] ="pwd";
    data->builtins[0] = ft_pwd;

    int i = 1;
    while (i < 7)
    {
        data->cmd_names[i] = NULL;
        data->builtins[i] = NULL;
        i++;
    }
}