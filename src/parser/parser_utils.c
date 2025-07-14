/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhivoto <mzhivoto@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 00:38:32 by mzhivoto          #+#    #+#             */
/*   Updated: 2025/07/15 00:42:05 by mzhivoto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_redirect_type(t_token *token)
{
	if (token->type == REDIR_OUT || token->type == REDIR_APPEND
		|| token->type == REDIR_IN || token->type == HEREDOC)
	{
		return (1);
	}
	else
		return (0);
}

void	delete_empty_tokens(t_token **head)
{
	t_token	*current;
	t_token	*tmp;

	current = *head;
	while (current)
	{
		if (current->value && current->value[0] == '\0')
		{
			tmp = current;
			if (current->prev)
				current->prev->next = current->next;
			else
				*head = current->next;
			if (current->next)
				current->next->prev = current->prev;
			current = current->next;
			free(tmp->value);
			free(tmp);
		}
		else
			current = current->next;
	}
}
