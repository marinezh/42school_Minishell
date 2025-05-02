#include "minishell.h"

int ft_pwd(t_data *data, t_command *cmd)
{
	char *pwd;

    (void)data;
	(void)cmd;
	pwd = getcwd(NULL, 0);
	if (pwd == NULL)
    {
        perror("pwd");
		return (1);
    }
	printf("%s\n", pwd);
	free(pwd);
	return (0);
}