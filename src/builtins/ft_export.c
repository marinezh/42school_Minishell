#include"minishell.h"

int count_strings(char **argv)
{
	int count;

	count = 0;
	while(argv[count])
		count++;
	return(count);
}


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
	//if there is no '=' in args and var exit do nothing
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

void	print_error_msg(char **args, char *msg)
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

int	is_var_name_valid(char *arg, char **args)
{
	int	i;

	i = 0;
	if (!((arg[0] >= 'a' && arg[0] <= 'z') ||
		(arg[0] >= 'A' && arg[0] <= 'Z') ||
		arg[0] == '_'))
	{
		print_error_msg(args, ": variable name is invalid\n");
		return (0);
	}
	i = 1;
	while (arg[i] && arg[i] != '=')
	{
		if (!((arg[i] >= 'a' && arg[i] <= 'z') ||
			(arg[i] >= 'A' && arg[i] <= 'Z') ||
			(arg[i] >= '0' && arg[i] <= '9') ||
			arg[i] == '_'))
		{
			print_error_msg(args, ": variable name is invalid\n");
			return (0);
		}
		i++;
	}
	return (1);
}

int	ft_export(t_data *data, t_command *cmd)
{
	int		arg_count;
	int		i;
	int		name_len;
	t_env	*cur;
	int 	found;

	i = 1;
	arg_count = count_strings(cmd->args);
	printf("arg_count - %d\n", arg_count);
	if (arg_count == 1)
		print_current_envp(data, cmd);
	else
	{
		while (i < arg_count)
		{
			if (cmd->args[i][0] == '-')
			{
				print_error_msg(cmd->args, ": command with option is invalid\n");
				break ;
			}
			if (!is_var_name_valid(cmd->args[i], cmd->args))
				break ;
			printf("arg 2 - %s\n", cmd->args[i]);
			name_len = var_name_len(cmd->args[i]);
			found = 0;
			cur = data->envp_list;
			printf("name len - %d\n", name_len);
			while (cur != NULL)
			{
				if (ft_strncmp(cur->key, cmd->args[i], name_len) == 0 &&
					cur->key[name_len] == '\0')
				{
						printf("the match - %s\n", cur->key);
						update_var_value(data, cur, cmd->args[i]);
						found = 1;
						break ;
				}
				cur = cur->next;
			}
			if (!found)
				create_env_var(data, cmd->args[i]);
			i++;
		}
	}
	return (0);
}

//export - prints variables in alphabetic order!
//export -p - should program notify about not-handling flags!

//1 - validate variables names created with export
// check -(start and follow) before adding to linked list
//2 - edge cases (e.g. export =value, ""=value, export+=value)
