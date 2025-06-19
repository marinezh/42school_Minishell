#include "minishell.h"


void remove_outer_quotes(t_token *tokens)
{
	t_token *current = tokens;
	
	while (current)
	{
		if (!current->value)
		{
			current = current->next;
			continue;
		}
		int i = 0, j = 0;
		char *input = current->value;
		char *result = malloc(ft_strlen(input) + 1);
		if (!result)
			return;
	
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
				result[j++] = input[i++];
		}
		result[j] = '\0';
		free(current->value);
		current->value = result;
		current = current->next;
	}
}
void remove_quotes_from_command_args(t_command *commands)
{
    t_command *current = commands;
    
    while (current)
    {
        // Remove quotes from arguments
        if (current->args)
        {
            int i = 0;
            while (current->args[i])
            {
                remove_outer_quotes_from_string(current->args[i]);
                i++;
            }
        }
        
        // Remove quotes from file names (preserving heredoc behavior)
        if (current->redirections)
            remove_quotes_from_files(current->redirections);
        if (current->in)
            remove_quotes_from_files(current->in);
        if (current->out)
            remove_quotes_from_files(current->out);
        
        current = current->next;
    }
}

void remove_outer_quotes_from_string(char *str)
{
    int i = 0;
    int j = 0;
    int len = ft_strlen(str);
    char *temp = (char *)malloc(len + 1);
    
    if (!temp)
        return;
    
    char in_quote = 0;
    while (str[i])
    {
        if ((str[i] == '\'' || str[i] == '"') && !in_quote)
        {
            // Start of quote
            in_quote = str[i];
            i++;
        }
        else if (str[i] == in_quote)
        {
            // End of quote
            in_quote = 0;
            i++;
        }
        else
        {
            // Copy character
            temp[j++] = str[i++];
        }
    }
    temp[j] = '\0';
    
    // Copy back to original
    ft_strlcpy(str, temp, len + 1);
    free(temp);
}

// void remove_quotes_from_files(t_files *files)
// {
//     t_files *current = files;
    
//     while (current)
//     {
//         // Skip if we want to preserve quotes for heredoc expansion check
//         if (current->type == HEREDOC)
//         {
//             // For heredocs, we need to be careful:
//             // 1. Check for quotes first to set expand_vars flag
//             int len = ft_strlen(current->name);
//             if (len >= 2 && current->name[0] == '\'' && current->name[len - 1] == '\'')
//             {
//                 // Single-quoted heredoc delimiter - don't expand variables
//                 current->expand_vars = 0;
//             }
//             else
//             {
//                 // Unquoted or double-quoted delimiter - do expand variables
//                 current->expand_vars = 1;
//             }
            
//             // 2. Then remove the quotes
//             //remove_outer_quotes_from_string(current->name);
//         }
//         else
//         {
//             // For regular files, just remove quotes
//             remove_outer_quotes_from_string(current->name);
//         }
        
//         current = current->next;
//     }
// }
void remove_quotes_from_files(t_files *files)
{
    t_files *current = files;

    while (current)
    {
        // For regular files, remove quotes
        if (current->type != HEREDOC)
            remove_outer_quotes_from_string(current->name);

        current = current->next;
    }
}
