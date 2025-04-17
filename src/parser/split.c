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
	printf("count %d\n", count);
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

int skip_quotes(char *str, int *j)
{
	
	char quote = str[*j];
	(*j)++;
	while(str[*j] && str[*j] != quote)
	{
		(*j)++;
	}
	if (str[*j] != quote)
	{
		printf("quotes not closed\n");
		return (-1);
	}
	if (str[*j] == quote)
			(*j)++;
	return 0;
}

char **ft_split_2(char *str, char delimiter)
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
				if (process_quotes(str, NULL, &j, NULL, 0) == -1)
					break ;
			}
			else 
			{
				while (str[j] && str[j] != delimiter)
					j++;
			}
			result[i++] = word_dup(&str[start], j - start); // Copy the word and store it in the array
		}
	}
	result[i] = NULL;
	return result;
}
