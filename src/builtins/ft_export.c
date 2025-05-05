#include"minishell.h"

int count_strings(char **argv)
{
	int count;

	count = 0;
	while(argv[count])
		count++;
	return(count);
}

void    print_current_envp(t_data *data, t_command *cmd)
{
	int i;

	i = 0;
	(void)cmd;
	if (data->envp_f)
	{
		update_envp_array(data, data->envp_list);
		data->envp_f = 0;
	}
	if (data->envp)
	{
		while (data->envp[i])
		{
			printf("declare -x %s\n", data->envp[i]);
			i++;
		}
	}
}
int var_name_len(char *name, int *equal_s)
{
	int count;

	count = 0;
	while (name[count] && name[count] != '=')
		count++;
	if (name[count] == '=')
		*equal_s = 1;
	return(count);
}

void	update_var_value(t_data *data, t_env *env_var, char *arg, int equal_s)
{
	char	*ptr;
	char	*dup_str;
	char	*newstr;

	ptr	= ft_strchr(arg, '=');
	if (equal_s && ptr)
	{
		newstr = ptr + 1;
		if (*newstr == '\0')
		{
			printf("ptr - %s\n", newstr);
			dup_str = ft_strdup("");
		}
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
		node_add_last(&data->envp_list, n_node);
}

int	ft_export(t_data *data, t_command *cmd)
{
	int		arg_count;
	int		i;
	int		name_len;
	int		equal_s;
	t_env	*cur;
	int 	found;

	i = 1;
	equal_s = 0;
	cur = data->envp_list;
	arg_count = count_strings(cmd->args);
	printf("arg_count - %d\n", arg_count);
	if (arg_count == 1)
		print_current_envp(data, cmd);
	else
	{
		while (i < arg_count)
		{
			printf("arg 2 - %s\n", cmd->args[i]);
			name_len = var_name_len(cmd->args[i], &equal_s);
			found = 0;
			printf("name len - %d\n", name_len);
			while (cur != NULL)
			{
				if (ft_strncmp(cur->key, cmd->args[i], name_len) == 0)
				{
					if (cur->key[name_len] == '\0')
					{
						printf("the match - %s\n", cur->key);
						update_var_value(data, cur, cmd->args[i], equal_s);
						found = 1;
						break ;
						printf("new - %s\n", cur->value);
					}
				}
				cur = cur->next;
			}
			if (!found)
				create_env_var(data, cmd->args[i]);
			cur = data->envp_list;
			i++;
		}
	}

	return (0);
}

//export - prints variables in alphabetic order!
//export -p - should program notify about not-handling flags!
