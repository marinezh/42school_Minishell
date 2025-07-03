#include"minishell.h"

int var_name_len(char *name)
{
	int     count;

	count = 0;
	while (name[count] && name[count] != '=')
		count++;
	if (name[count] == '=')
		count++;
	return(count);
}

t_env *find_env_node(t_data *data, char *env_var)
{
    int     name_len;
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

int	count_args(char **args)
{
	int		count;

	count = 0;
	while (args && args[count])
		count++;
	return (count);
}
