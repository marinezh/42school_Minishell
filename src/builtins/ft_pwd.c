#include "minishell.h"

int ft_pwd(t_data *data, t_command *cmd)
{
	t_env	*pwd_node;
	char 	*pwd;

    if (cmd->args[1])
    {
        ft_putstr_fd("minishell: pwd: ", STDERR_FILENO);
        ft_putstr_fd("options are not supported\n", STDERR_FILENO);
        return (ERROR_GENERIC);
    }
	pwd_node = find_env_name(data, "PWD");
	if (pwd_node && pwd_node->value)
	{
		printf("%s\n", pwd_node->value);
		return (0);
	}
	pwd = getcwd(NULL, 0);
	if (pwd == NULL)
    {
        perror("pwd");
		return (ERROR_GENERIC);
    }
	printf("%s\n", pwd);
	free(pwd);
	return (0);
}

//bash first checks if PWD env exit and prints it
//if not exit then only system call getcwd