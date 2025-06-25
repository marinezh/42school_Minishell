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
		handle_error_arg(data, "", ERR_PARSING_PIPE, 2);
		data->status = 2;
		//printf("ONE PIPE\n");
		return 1;
	}
	while(token)
	{
		// if (token->value && check_unclosed_quotes(token->value))
		// {
		// 	handle_error_arg(data, "", "minishell: unclosed quotes !!!", 2);
		// 	//makedata->status = 2;
		// 	//printf("QUOTES\n");
		// 	return (1);
		// }
		
		if(token->type == PIPE && (!token->next || token->next->type == PIPE))
		{
			handle_error_arg(data, "", ERR_PARSING_PIPE, 2);
			//data->status = 2;
			//printf("TW0 PIPES\n");
			return (1);
		}
		// case < > << >> (newline error)
		if ((token->type == REDIR_APPEND || token->type == REDIR_IN || 
			token->type == REDIR_OUT || token->type == HEREDOC) && !token->next)
		{
			handle_error_arg(data, "", ERR_PARSING_RED, 2);
			
			//data->status = 2;
			//printf("FOUR\n");
		
			return (1);
		}
	
        // Handle the special case of REDIR_APPEND followed by REDIR_OUT >>> case 
        else if ((token->type == REDIR_OUT || token->type == REDIR_APPEND || token->type == REDIR_IN || token->type == HEREDOC)
				 && token->next && (token->next->type == REDIR_OUT))
        {
            handle_error_arg(data, "", ERR_PARSING_OUT, 2);
			//printf(" syntax error near unexpected token `>'\n");
			//printf(">>>\n");
            return 1;
        }
		// else if((token->type == REDIR_APPEND || token->type == REDIR_IN || 
		// 	token->type == REDIR_OUT || token->type == HEREDOC) &&
		// 	(!token->next || token->next->type == REDIR_APPEND ||
		// 	token->next->type == REDIR_IN || token->next->type == REDIR_OUT ||
		// 	token->next->type == HEREDOC))
		// {
		// 	handle_error_arg(data, "", ERR_PARSING_RED2, 2);
			
		// 	//data->status = 2;
		// 	//printf("FOUR\n");
		// 	return (1);
		// }
		else if ((token->type == REDIR_OUT || token->type == REDIR_APPEND || token->type == REDIR_IN || token->type == HEREDOC) && token->next && (token->next->type == REDIR_APPEND))
		{
			handle_error_arg(data, "", ERR_PARSING_APP, 2);
			//printf(" syntax error near unexpected token `>'\n");
		// 	//data->status = 2;
		// 	//printf("FOUR\n");
			return (1);
		}
		else if ((token->type == REDIR_OUT || token->type == REDIR_APPEND || token->type == REDIR_IN || token->type == HEREDOC) && token->next && (token->next->type == REDIR_IN))
		{
			handle_error_arg(data, "", ERR_PARSING_IN, 2);
			//printf(" syntax error near unexpected token `>>'\n");
		// 	//data->status = 2;
		// 	//printf("FOUR\n");
			return (1);
		}
		else if ((token->type == REDIR_OUT || token->type == REDIR_APPEND || token->type == REDIR_IN || token->type == HEREDOC) && token->next && (token->next->type == HEREDOC))
		{
			handle_error_arg(data, "", ERR_PARSING_HER, 2);
			//printf(" syntax error near unexpected token `>>'\n");
		// 	//data->status = 2;
		// 	//printf("FOUR\n");
			return (1);
		}
		else if((token->type == REDIR_APPEND || token->type == REDIR_IN || 
			token->type == REDIR_OUT || token->type == HEREDOC) &&
			(!token->next || token->next->type == PIPE ))
		{
			handle_error_arg(data, "", ERR_PARSING_PIPE, 2);
		
			//data->status = 2;
			//printf("FIVE\n");
			return (1);
		}

		token = token->next;
	}
	return 0;
}


