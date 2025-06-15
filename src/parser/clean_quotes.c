#include "minishell.h"

// int is_closed_quote(t_token *token)
// {
// 	int i = 0;
// 	char quotes = '\'';
// 	if (token->value[i] == quotes)
// 	{
// 		while (token->value[i] && token->value[i] != quotes)
// 			i++;

// 	}
// }
// void clean_quotes(t_token *token)
// {
// 	int i = 0;
// 	char quotes = '\'';
// 	while (token->value[i])
// 	{
// 		if (token->value[i] == quotes)
// 			token->value[i] = '\0';
// 	}
	
// }
void remove_outer_quotes(t_token *token)
{
    if (!token || !token->value)
        return;

    int i = 0, j = 0;
    char *input = token->value;
    char *result = malloc(ft_strlen(input) + 1);
    if (!result)
        return; // handle malloc failure

    while (input[i])
    {
        if (input[i] == '\'' || input[i] == '"')
        {
            char quote = input[i++];
            while (input[i] && input[i] != quote)
                result[j++] = input[i++];
            if (input[i] == quote)
                i++; // skip closing quote
        }
        else
        {
            result[j++] = input[i++];
        }
    }
    if (token->value)
        free(token->value);

    token->value = result;
}
