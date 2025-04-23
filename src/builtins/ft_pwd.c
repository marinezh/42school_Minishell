#include "minishell.h"

int ft_pwd(t_llist *list, t_edata edata)
{
	char *pwd;
	
    (void)edata;
    (void)list;
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