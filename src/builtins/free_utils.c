/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikozhina <ikozhina@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 10:40:28 by ikozhina          #+#    #+#             */
/*   Updated: 2025/07/12 10:46:01 by ikozhina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_env_node(t_env *node)
{
	if (node)
	{
		free(node->value);
		free(node->key);
		free(node);
	}
}

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
