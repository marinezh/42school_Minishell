#include"minishell.h"

int var_name_len(char *name)
{
	int count;

	count = 0;
	while (name[count] && name[count] != '=')
		count++;
	if (name[count] == '=')
		count++;
	return(count);
}

void	print_error_msg(char *cmd, char *msg)
{
    ft_putstr_fd("minishell: ", STDERR_FILENO);
    ft_putstr_fd(cmd, STDERR_FILENO);
    ft_putstr_fd(msg, STDERR_FILENO);
}

void	print_error(char **args, char *msg)
{
	int i;

	printf("usage: ");
	i = 0;
	while (args[i])
	{
		printf("%s", args[i]);
		if (args[i + 1])
			printf(" ");
		i++;
	}
	printf("%s", msg);
}

t_env *find_env_name(t_data *data, char *env_var)
{
    int name_len;
    t_env	*cur;
    
    name_len = var_name_len(env_var);
    cur = data->envp_list;
    while (cur != NULL)
    {
        if (ft_strncmp(cur->key, env_var, name_len) == 0 &&
            (cur->key[name_len] == '\0' || cur->key[name_len] == '='))
            return (cur);
        cur = cur->next;
    }
    return (NULL);
}
