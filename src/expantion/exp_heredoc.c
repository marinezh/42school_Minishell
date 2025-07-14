/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_heredoc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhivoto <mzhivoto@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 00:47:13 by mzhivoto          #+#    #+#             */
/*   Updated: 2025/07/15 00:53:24 by mzhivoto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	process_token_variables(t_token *tok, t_data *data)
{
	int	i;

	i = 0;
	while (tok->value && tok->value[i])
	{
		if (tok->value[i] == '$')
		{
			if (tok->value[i + 1] == '?')
			{
				if (!process_status_var(tok, data, &i))
					return (0);
				continue ;
			}
			else if (ft_isalpha(tok->value[i + 1]) || tok->value[i + 1] == '_')
			{
				if (!process_expantion(tok, data, &i))
					return (0);
				continue ;
			}
		}
		i++;
	}
	return (1);
}

int	expand_heredoc_file(t_token *tokens, t_data *data)
{
	t_token	*current;

	if (!tokens || !data)
		return (0);
	current = tokens;
	while (current)
	{
		if (!process_token_variables(current, data))
			return (0);
		current = current->next;
	}
	return (1);
}

char	*expand_heredoc_line(char *input, t_data *data)
{
	t_token	temp;

	temp.value = ft_strdup(input);
	if (!temp.value)
		return (NULL);
	temp.type = WORD;
	temp.next = NULL;
	temp.prev = NULL;
	if (!expand_heredoc_file(&temp, data))
	{
		free(temp.value);
		return (NULL);
	}
	return (temp.value);
}
