#include"minishell.h"

void init_data(t_edata *edata)
{
    edata->cmd_names[0] ="pwd";
    edata->builtins[0] = ft_pwd;
}