/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikozhina <ikozhina@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 10:33:53 by ikozhina          #+#    #+#             */
/*   Updated: 2025/07/12 10:33:55 by ikozhina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	run_bltin(t_data *data, t_command *cmd)
{
	int		i;
	int		status;
	char	**args;

	i = 0;
	args = cmd->args;
	while (i < 7)
	{
		if (data->cmd_names[i] && ft_strcmp(args[0], data->cmd_names[i]) == 0)
		{
			status = data->builtins[i](data, cmd);
			data->status = status;
			return (status);
		}
		i++;
	}
	return(-1);
}

