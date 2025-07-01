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

int error_check(t_token *token, t_data *data)
{
	if (token && token->type == PIPE)
	{
		handle_error_arg(data, "", ERR_PARSING_PIPE, 2);
		data->status = 2;
		return 1;
	}
	while(token)
	{
		if(token->type == PIPE && (!token->next || token->next->type == PIPE))
		{
			handle_error_arg(data, "", ERR_PARSING_PIPE, 2);
			return (1);
		}
		// case < > << >> (newline error)
		if (is_redirect_type(token) && !token->next)
		{
			handle_error_arg(data, "", ERR_PARSING_RED, 2);
			return (1);
		}
		// Handle the special case of REDIR_APPEND followed by REDIR_OUT >>> case 
		else if (is_redirect_type(token) && token->next && (token->next->type == REDIR_OUT))
		{
			handle_error_arg(data, "", ERR_PARSING_OUT, 2);
			return 1;
		}
		else if (is_redirect_type(token)
			&& token->next && (token->next->type == REDIR_APPEND))
		{
			handle_error_arg(data, "", ERR_PARSING_APP, 2);
			return (1);
		}
		else if (is_redirect_type(token)
			&& token->next && (token->next->type == REDIR_IN))
		{
			handle_error_arg(data, "", ERR_PARSING_IN, 2);
			return (1);
		}
		else if (is_redirect_type(token) && token->next && (token->next->type == HEREDOC))
		{
			handle_error_arg(data, "", ERR_PARSING_HER, 2);
			return (1);
		}
		else if((token->type == REDIR_APPEND || token->type == REDIR_IN || 
			token->type == REDIR_OUT || token->type == HEREDOC) &&
			(!token->next || token->next->type == PIPE ))
		{
			handle_error_arg(data, "", ERR_PARSING_PIPE, 2);
			return (1);
		}

		token = token->next;
	}
	return 0;
}


