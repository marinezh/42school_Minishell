#include <minishell.h>

int word_count(char *str, char delimeter)
{
	int i = 0;
	int count = 0;
	int in_word = 0;;
	while (str[i])
	{
		if(str[i] == delimeter)
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
static char *word_dup(char *str, int len)
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

char **quote_safe_split(char *str, char delimiter)
{
	int words = word_count(str, ' ');
	char **result = (char **)malloc(sizeof(char *) * (words + 1));
	int i = 0; 
	int j = 0;
	
	if (!result)
		return NULL;
	while (str[j])
	{
		while (str[j] && (str[j] == delimiter))
			j++;
		if (str[j])
		{
			int start = j;
			if (str[j] == '\'' || str[j] == '\"')
			{
				if (skip_quoted_seg(str, &j) == -1)
				{
					free_split_result(result, i);
					return NULL;
				}
			}
			else 
			{
				int in_quote = 0;
				char quote_char = 0;

				while (str[j] && (in_quote || str[j] != delimiter))
				{
					if ((str[j] == '\'' || str[j] == '\"'))
					{
						if (!in_quote)
						{
							in_quote = 1;
							quote_char = str[j];
						}
						else if (str[j] == quote_char)
							in_quote = 0;
					}
					j++;
				}
			}
			result[i] = word_dup(&str[start], j - start); // Copy the word and store it in the array
			if (!result[i])
			{
				free_split_result(result, i);
				return NULL;
			}
			i++;
		}
	}
	result[i] = NULL;
	return result;
}
