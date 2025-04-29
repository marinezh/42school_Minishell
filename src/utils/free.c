#include "minishell.h"

// void free_tokens(char **tokens)
// {
// 	int i = 0;

// 	if (!tokens)
// 		return;
// 	while (tokens[i])
// 	{
// 		free(tokens[i]);
// 	}
// 	free(tokens);
// }
// void free_tokens(t_token *tokens)
// {
// 	t_token *tmp;
// 	while (tokens != NULL) {
// 		tmp = tokens;
// 		tokens = tokens->next;
// 		free(tmp->value);		// Free the value
// 		free(tmp);				// Free the token itself
// 	}
// }