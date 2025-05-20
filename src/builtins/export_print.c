#include "minishell.h"

void sort_envp_by_key(char **envp)
{
	int		i;
	int		swap;
	char	*tmp;

	swap = 1;
	while (swap)
	{
		swap = 0;
		i = 0;
		while (envp[i])
		{
			if (envp[i + 1] && ft_strcmp(envp[i], envp[i + 1]) > 0)
			{
				tmp = envp[i];
				envp[i] = envp[i + 1];
				envp[i + 1] = tmp;
				swap = 1;
			}
			i++;
		}
	}
}

void	print_export_format(char **envp)
{
	int		i;
	char	*ptr;
	char	*value;
	int		key_len;

	i = 0;
	while (envp[i])
	{
		ptr = ft_strchr(envp[i], '=');
		if (ptr)
		{
			key_len = ptr - envp[i];
			value = ptr + 1;
		}
		else
		{
			key_len = (int)ft_strlen(envp[i]);
			value = NULL;
		}
		if (value)
			printf("declare -x %.*s=\"%s\"\n", key_len, envp[i], value);
		else
			printf("declare -x %.*s\n", key_len, envp[i]);
		i++;
	}
}

int	print_current_envp(t_data *data, t_command *cmd)
{
	(void)cmd;
	if (data->envp_f)
	{
		update_envp_array(data, data->envp_list);
		data->envp_f = 0;
	}
	if (data->envp)
	{
		sort_envp_by_key(data->envp);
		print_export_format(data->envp);
		free_double_array(data->envp);
		data->envp = NULL;
		data->envp_f = 1;
	}
	return (0);
}
