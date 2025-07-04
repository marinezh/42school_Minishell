#include"minishell.h"

int count_name_len(char *name)
{
	int     count;

	count = 0;
	while (name[count] && name[count] != '=')
		count++;
	return(count);
}

t_env *find_env_node(t_data *data, char *env_var)
{
    int     var_name_len;
    int     cur_name_len;
    t_env	*cur;

    var_name_len = count_name_len(env_var);
    cur = data->envp_list;
    while (cur != NULL)
    {
        cur_name_len = count_name_len(cur->key);
        if (cur_name_len == var_name_len && 
            ft_strncmp(cur->key, env_var, var_name_len) == 0)
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
