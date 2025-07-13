#include "minishell.h"

int	check_pipe_errors(t_token *token, t_data *data)
{
	if (!token->next || token->next->type == PIPE)
	{
		handle_error_arg(data, "", ERR_PARSING_PIPE, 2);
		return (1);
	}
	return (0);
}

int	check_redirect_syntax(t_token *token, t_data *data)
{
	if (!token->next)
	{
		handle_error_arg(data, "", ERR_PARSING_NEW, 2);
		return (1);
	}
	if (token->next && token->next->type == PIPE)
	{
		handle_error_arg(data, "", ERR_PARSING_PIPE, 2);
		return (1);
	}
	return (0);
}

int	check_invalid_redirect_sequence(t_token *token, t_data *data)
{
	if (!token->next)
		return (0);
	if (token->next->type == REDIR_OUT)
	{
		handle_error_arg(data, "", ERR_PARSING_OUT, 2);
		return (1);
	}
	else if (token->next->type == REDIR_APPEND)
	{
		handle_error_arg(data, "", ERR_PARSING_APP, 2);
		return (1);
	}
	else if (token->next->type == REDIR_IN)
	{
		handle_error_arg(data, "", ERR_PARSING_IN, 2);
		return (1);
	}
	else if (token->next->type == HEREDOC)
	{
		handle_error_arg(data, "", ERR_PARSING_HER, 2);
		return (1);
	}
	return (0);
}

int	error_check(t_token *token, t_data *data)
{
	if (token && token->type == PIPE)
	{
		handle_error_arg(data, "", ERR_PARSING_PIPE, 2);
		data->status = 2;
		return (1);
	}
	while (token)
	{
		if (token->type == PIPE)
		{
			if (check_pipe_errors(token, data))
				return (1);
		}
		else if (is_redirect_type(token))
		{
			if (check_redirect_syntax(token, data))
				return (1);
			if (check_invalid_redirect_sequence(token, data))
				return (1);
		}
		token = token->next;
	}
	return (0);
}
