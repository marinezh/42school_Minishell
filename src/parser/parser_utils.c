#include "minishell.h"

int is_redirect_type(t_token *token)
{
	if (token->type == REDIR_OUT || token->type == REDIR_APPEND
		|| token->type == REDIR_IN || token->type == HEREDOC)
	{
		return 1;
	}
	else
		return 0;
}