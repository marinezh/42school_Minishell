#include "minishell.h"

void free_tokens(char **tokens)
{
    int i = 0;

    if (!tokens)
        return;
    while (tokens[i])
    {
        free(tokens[i]);
    }
    free(tokens);
}