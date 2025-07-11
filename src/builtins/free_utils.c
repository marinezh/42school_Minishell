#include "minishell.h"

void	free_env_list(t_env **env)
{
	t_env	*tmp;
	t_env	*node;

	if (!env || !*env)
		return ;
	node = *env;
	while (node)
	{
		tmp = node;
		node = node->next;
		free_env_node(tmp);
	}
	*env = NULL;
}

void	free_env_node(t_env *node)
{
	if (node)
	{
		free(node->value);
		free(node->key);
		free(node);
	}
}