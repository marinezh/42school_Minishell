#include "minishell.h"

char *expand_heredoc_line(char *input, t_data *data)
{
	t_token temp;
	(void)input;
	temp.value = ft_strdup(input);
	if (!temp.value)
		return (NULL);
	temp.type = WORD;
	temp.next = NULL;
	expand_variables(&temp, data, 0);
	return temp.value;
}
