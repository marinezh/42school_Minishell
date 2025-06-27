#include "minishell.h"

void handle_heredoc_delimiter(t_files *node, char *delimiter)
{
    size_t len = strlen(delimiter);
    
    // If delimiter is quoted, don't expand variables in heredoc content
    if ((delimiter[0] == '\'' && delimiter[len-1] == '\'') || 
        (delimiter[0] == '\"' && delimiter[len-1] == '\"'))
    {
        // Remove quotes from delimiter
        node->name = ft_substr(delimiter, 1, len-2);
        node->to_expand = 0;  // Don't expand variables in content
    }
    else
    {
        node->name = ft_strdup(delimiter);
        node->to_expand = 1;  // Expand variables in content
    }
}


char *expand_heredoc_line(char *input, t_data *data)
{
	t_token temp;
	(void)input;
	temp.value = ft_strdup(input);
	if (!temp.value)
		return (NULL);
	temp.type = WORD;
	temp.next = NULL;
	expand_variables_her(&temp, data);
	return temp.value;
}
