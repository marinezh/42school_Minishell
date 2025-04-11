/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhivoto <mzhivoto@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 16:02:40 by mzhivoto          #+#    #+#             */
/*   Updated: 2025/04/11 15:39:12 by mzhivoto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	print_prompt(t_data *data)
{
	data->input = readline("minishell$ ");
	if (!data->input)
		return (-1);
	return (1);
}

int	parsing(t_data *data)
{
	printf(data->input);
	return (0);
}