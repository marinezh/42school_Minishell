#include <minishell.h>

int	word_count(char *str)
{
	int	i;
	int	count;
	int	in_word;

	i = 0;
	count = 0;
	in_word = 0;
	if (!str || !*str)
		return (0);
	while (str[i])
	{
		if (is_whitespace(str[i]))
			in_word = 0;
		else if (!in_word)
		{
			in_word = 1;
			count++;
		}
		i++;
	}
	return (count);
}

char	*word_dup(char *str, int len)
{
	int		i;
	char	*word;

	i = 0;
	word = (char *)malloc(sizeof(char) * (len + 1)); //checked 
	if (!word)
		return (NULL);
	while (i < len)
	{
		word[i] = str[i];
		i++;
	}
	word[len] = '\0';
	return (word);
}

int	is_whitespace(char c)
{
	return (c == ' ' || c == '\t' || c == '\n' || c == '\r' || c == '\v'
		|| c == '\f');
}

int	skip_whitespaces(char *str, int j)
{
	while (str[j] && (is_whitespace(str[j])))
		j++;
	return (j);
}
