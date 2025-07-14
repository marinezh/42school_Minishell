/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_handlers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhivoto <mzhivoto@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 00:38:20 by mzhivoto          #+#    #+#             */
/*   Updated: 2025/07/15 01:06:53 by mzhivoto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**realloc_args(char **args, int count, char *value)
{
	int		i;
	char	**new_args;

	i = 0;
	new_args = malloc(sizeof(char *) * (count + 2));
	if (!new_args)
		return (NULL);
	while (i < count)
	{
		new_args[i] = args[i];
		i++;
	}
	new_args[count] = ft_strdup(value);
	new_args[count + 1] = NULL;
	if (args)
		free(args);
	return (new_args);
}

void	handle_pipe(t_command *cur, t_token **token_list, t_command **cur_cmd)
{
	cur->pipe = 1;
	*cur_cmd = NULL;
	*token_list = (*token_list)->next;
}

int	handle_redirection(t_command *cur, t_token **token_list)
{
	int	redir_type;

	redir_type = (*token_list)->type;
	*token_list = (*token_list)->next;
	if (*token_list && ((*token_list)->type == WORD
			|| (*token_list)->type == FILE_NAME))
	{
		if (!add_redirection(cur, (*token_list)->value, redir_type))
		{
			return (0);
		}
		*token_list = (*token_list)->next;
		return (1);
	}
	return (1);
}

int	handle_word_token(t_command *cur, t_token **token_list)
{
	int	argc;

	argc = 0;
	while (cur->args && cur->args[argc])
		argc++;
	cur->args = realloc_args(cur->args, argc, (*token_list)->value);
	if (!cur->args)
		return (0);
	*token_list = (*token_list)->next;
	return (1);
}

void	append_to_list(t_files **list, t_files *node)
{
	t_files	*cur;

	if (*list == NULL)
	{
		*list = node;
		return ;
	}
	cur = *list;
	while (cur->next)
		cur = cur->next;
	cur->next = node;
}
