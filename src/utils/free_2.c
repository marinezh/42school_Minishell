/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhivoto <mzhivoto@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 00:39:26 by mzhivoto          #+#    #+#             */
/*   Updated: 2025/07/15 01:06:08 by mzhivoto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Frees multiple string pointers
 * Function accepts a variable number of string pointers and frees each one
 * The last argument must be NULL to indicate the end of arguments
 */
void	free_strings(char *str, ...)
{
	va_list	args;
	char	*ptr;

	if (str)
		free(str);
	va_start(args, str);
	ptr = va_arg(args, char *);
	while (ptr)
	{
		free(ptr);
		ptr = va_arg(args, char *);
	}
	va_end(args);
}

void	free_exp_parts(t_exp_parts *parts)
{
	if (!parts)
		return ;
	if (parts->status_str)
		free(parts->status_str);
	if (parts->prefix)
		free(parts->prefix);
	if (parts->suffix)
		free(parts->suffix);
	if (parts->new_value)
		free(parts->new_value);
	if (parts->final_value)
		free(parts->final_value);
	*parts = (t_exp_parts){0};
}
