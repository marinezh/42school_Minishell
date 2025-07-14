/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikozhina <ikozhina@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 10:41:09 by ikozhina          #+#    #+#             */
/*   Updated: 2025/07/14 14:36:20 by ikozhina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_n_flag_valid(char *argv)
{
	int	i;

	i = 1;
	if (argv[0] != '-' || argv[1] == '\0')
		return (0);
	while (argv[i])
	{
		if (argv[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

int	ft_echo(t_data *data, t_command *cmd)
{
	int		i;
	char	**argv;
	int		n_flag;

	(void)data;
	argv = cmd->args;
	n_flag = 0;
	i = 1;
	while (argv[i] && is_n_flag_valid(argv[i]))
	{
		n_flag = 1;
		i++;
	}
	while (argv[i])
	{
		ft_putstr(argv[i]);
		if (argv[i + 1])
			ft_putchar(' ');
		i++;
	}
	if (!n_flag)
		ft_putchar('\n');
	return (0);
}
