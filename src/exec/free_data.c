#include"minishell.h"

void	free_envp_array(char **envp)
{
	int	i;

	i = 0;
	if (envp)
	{
		while (envp[i])
		{
			free(envp[i]);
			i++;
		}
	}
	free(envp);
}

void	free_env_list(t_env *env)
{
	t_env	*tmp;

	while (env)
	{
		tmp = env;
		env = env->next;
		free(tmp->key);
		free(tmp->value);
		free(tmp);
	}
}