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

// char	*extract_unquoted_name(char *name)
// {
// 	char	*unquoted_name;
// 	int		len;

// 	len = ft_strlen(name);
// 	if (len >= 2 && ((name[0] == '\'' && name[len - 1] == '\'')
// 			|| (name[0] == '"' && name[len - 1] == '"')))
// 	{
// 		unquoted_name = ft_substr(name, 1, len - 2);
// 		return (unquoted_name);
// 	}
// 	return (ft_strdup(name));
// }

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
