#include "minishell.h"

int ft_pwd(t_data *data, t_command *cmd)
{
	t_env	*pwd_node;
	char 	*pwd;

    if (cmd->args[1] && cmd->args[1][0] == '-')
	{
		print_error_msg("pwd", MSG_NO_OPTIONS);
		return(ERR_GENERIC);
	}
	pwd_node = find_env_node(data, "PWD");
	if (pwd_node && pwd_node->value)
	{
		ft_putstr_fd(pwd_node->value, STDOUT_FILENO);
        ft_putstr_fd("\n", STDOUT_FILENO);
		return (0);
	}
	pwd = getcwd(NULL, 0);
	if (pwd == NULL)
    {
        perror("pwd");
		return (ERR_GENERIC);
    }
	ft_putstr_fd(pwd, STDOUT_FILENO);
    ft_putstr_fd("\n", STDOUT_FILENO);
	free(pwd);
	return (0);
}

//bash first checks if PWD env exit and prints it
//if not exit then only system call getcwd()
//in bash pwd - no argv and options possible