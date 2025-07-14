/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikozhina <ikozhina@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 10:41:19 by ikozhina          #+#    #+#             */
/*   Updated: 2025/07/14 14:36:25 by ikozhina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_env(t_data *data, t_command *cmd)
{
	int	i;

	i = 0;
	if (cmd->args[1])
	{
		print_error_msg("env", MSG_NO_OPTS_ARGS);
		return (ERR_GENERIC);
	}
	if (data->envp_f)
	{
		if (rebuild_envp_array(data, data->envp_list) == -1)
			return (ERR_GENERIC);
		data->envp_f = 0;
	}
	if (data->envp)
	{
		while (data->envp[i])
		{
			if (ft_strchr(data->envp[i], '='))
				printf("%s\n", data->envp[i]);
			i++;
		}
	}
	return (0);
}
