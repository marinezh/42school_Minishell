#include <minishell.h>

int word_count(char *str, char delimiter)
{
	int i = 0;
	int count = 0;
	int in_word = 0;

	if (!str || !*str)
		return 0;
	// Special case: if string has no delimiter, return 1
	// if (!strchr(str, delimiter)) //double check , do i need this ?
	// 	return 1;
	while (str[i])
	{
		if(str[i] == delimiter)
			in_word = 0;
		else if (!in_word)
		{
			in_word = 1;
			count++;
		}
		i++;
	}
	//printf("count %d\n", count);
	return count;
}
char *word_dup(char *str, int len)
{
	int i = 0;
	char *word = (char *)malloc(sizeof(char) * (len + 1));
	if (!word)
		return NULL;
	while(i < len)
	{
		word[i] = str[i];
		i++;
	}
	word[len] = '\0';
	return word;
}

// int skip_quoted_seg(char *input, int *i)
// {
// 	char quote; 
	
// 	quote = input[*i];
// 	(*i)++; // skip openning quote
// 	while (input[*i] && input[*i] != quote)
// 		(*i)++;
// 	if (!input[*i])
// 	{
// 		ft_putstr_fd("minishell:quotes are not closed", 2);
// 		//ft_putstr_fd(ERR_QUOTES, 2);
// 		return (-1);
// 	}
// 	(*i)++; // skip closing quote
// 	return (0);
// }

void	error_msg(char *msg)
{
	ft_putendl_fd(msg, 2);
}