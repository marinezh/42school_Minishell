#include"minishell.h"

void	update_var_value(t_data *data, t_env *env_var, char *arg)
{
	char	*ptr;
	char	*dup_str;
	char	*newstr;

	ptr	= ft_strchr(arg, '=');
	if (ptr)
	{
		newstr = ptr + 1;
		if (*newstr == '\0')
			dup_str = ft_strdup("");
		else
			dup_str = ft_strdup(newstr);
		free(env_var->value);
		if (dup_str)
			(env_var->value) = dup_str;
		data->envp_f = 1;
	}
}

void	create_env_var(t_data *data, char *arg)
{
	t_env	*n_node;

	n_node = create_env_node(arg);
	if (n_node)
	{
		node_add_last(&data->envp_list, n_node);
		data->envp_f = 1;
	}
}

int	is_var_name_valid(char *arg, int *special_var)
{
	int	i;

    if (arg[0] == '_' && (arg[1] == '\0' || arg[1] == '='))
    {
        *special_var = 1;
        return(1);
    }
	if (!(ft_isalpha(arg[0]) || arg[0] == '_'))
		return (0);
	i = 1;
	while (arg[i] && arg[i] != '=')
	{
		if (!(ft_isalpha(arg[i]) || ft_isdigit(arg[i]) || arg[i] == '_'))
			return (0);
		i++;
	}
	return (1);
}
void    process_env_var(t_data *data, char *env_var)
{
    t_env   *cur_env;

    cur_env = find_env_node(data, env_var);
    if (cur_env)
        update_var_value(data, cur_env, env_var);
    else
        create_env_var(data, env_var);
}

int	ft_export(t_data *data, t_command *cmd)
{
	int		i;
    int     special_var;
	int		had_error;

	i = 1;
    special_var = 0;
	had_error = 0;
	if (!cmd->args[1])
		return (print_current_envp(data, cmd));
	else
	{
		while (cmd->args[i])
		{
			if (cmd->args[i][0] == '-')
			{
				print_error("export: ", cmd->args[i], MSG_NO_OPTIONS);
				return (1);
			}
			if (!is_var_name_valid(cmd->args[i], &special_var))
			{
				print_error("export: ", cmd->args[i], MSG_INVALID_NAME);
				had_error = 1;
				i++;
				continue ;
			}
            if (!special_var)
                process_env_var(data, cmd->args[i]);
			i++;
		}
	}
	return (had_error);
}


//export - prints variables in alphabetic order!
//export -p - program notify about not-handling flags!

//1 - validate variables names created with export
// check -(start and follow) before adding to linked list
//2 - edge cases (e.g. export =value, ""=value, export+=value)
//3 - "export _" or "export _=" no error, but shouldn't go to process_env_var
