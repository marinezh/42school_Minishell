#include "minishell.h"

int ft_pwd(t_data *data)
{
	char *pwd;

    (void)data;
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