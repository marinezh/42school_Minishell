/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhivoto <mzhivoto@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 00:39:35 by mzhivoto          #+#    #+#             */
/*   Updated: 2025/07/15 00:43:37 by mzhivoto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_tokens(t_token *tokens)
{
	t_token	*tmp;

	while (tokens)
	{
		tmp = tokens->next;
		if (tokens->value)
			free(tokens->value);
		free(tokens);
		tokens = tmp;
	}
}

void	free_file_list(t_files *files)
{
	t_files	*tmp;

	while (files)
	{
		tmp = files;
		files = files->next;
		if (tmp->name)
			free(tmp->name);
		if (tmp->fd >= 0)
			close(tmp->fd);
		free(tmp);
	}
}

void	free_command_list(t_command *commands)
{
	t_command	*tmp;
	int			i;

	while (commands)
	{
		tmp = commands;
		commands = commands->next;
		if (tmp->args)
		{
			i = 0;
			while (tmp->args[i])
				free(tmp->args[i++]);
			free(tmp->args);
		}
		free_file_list(tmp->in);
		free_file_list(tmp->out);
		free_file_list(tmp->redirections);
		free(tmp);
	}
}

void	free_split_input(char **split)
{
	int	i;

	i = 0;
	if (!split)
		return ;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

void	free_split_result(char **result, int i)
{
	int	k;

	k = 0;
	while (k < i)
	{
		if (result[k])
			free(result[k]);
		k++;
	}
	free(result);
}
