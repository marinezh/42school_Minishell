#include "minishell.h"
int check_unclosed_quotes(char *str)
{
	int i = 0;
	char quote = 0;

	while (str[i])
	{
		if ((str[i] == '\'' || str[i] == '"'))
		{
			if (!quote)
				quote = str[i];
			else if (str[i] == quote)
				quote = 0;
		}
		i++;
	}
	return (quote != 0);
}

int error_check(t_token *token, t_data *data)
{
	// Check if command starts with a pipe
	if (token && token->type == PIPE)
	{
		printf("syntax error near unexpected token '|'\n");
		return 1;
	}
	while(token)
	{
		if (token->value && check_unclosed_quotes(token->value))
		{
			handle_error_arg(data, "", "minishell: unclosed quotes !!!", 2);
			return (1);
		}
		
		if(token->type == PIPE && (!token->next || token->next->type == PIPE))
		{
			handle_error_arg(data, "", ERR_PARSING_PIPE, 2);
			return (1);
		}
		else if((token->type == REDIR_APPEND || token->type == REDIR_IN || 
			token->type == REDIR_OUT || token->type == HEREDOC) &&
			(!token->next || token->next->type == REDIR_APPEND ||
			token->next->type == REDIR_IN || token->next->type == REDIR_OUT ||
			token->next->type == HEREDOC))
		{
			handle_error_arg(data, "", ERR_PARSING_RED, 2);
			return (1);
		}
		else if((token->type == REDIR_APPEND || token->type == REDIR_IN || 
			token->type == REDIR_OUT || token->type == HEREDOC) &&
			(!token->next || token->next->type == PIPE ))
		{
			handle_error_arg(data, "", ERR_PARSING_PIPE, 2);
			return (1);
		}
		// else if(token->type == PIPE && (!token->prev)) // think about do i need to use double linked list here
		// {
		// 	printf("syntax error | ls\n");
		// 	return (1);
		// }
		token = token->next;
	}
	return 0;
}