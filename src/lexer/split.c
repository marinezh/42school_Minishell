#include <minishell.h>

static int	process_quote_segment(char *str, int *j, int *in_quote,
		char *quote_char)
{
	if (!(*in_quote))
	{
		*in_quote = 1;
		*quote_char = str[*j];
	}
	else if (str[*j] == *quote_char)
		*in_quote = 0;
	(*j)++;
	return (0);
}

static int	find_word_end(char *str, int start)
{
	int		j;
	int		in_quote;
	char	quote_char;

	j = start;
	in_quote = 0;
	quote_char = 0;
	while (str[j] && (in_quote || !is_whitespace(str[j])))
	{
		if (str[j] == '\'' || str[j] == '\"')
			process_quote_segment(str, &j, &in_quote, &quote_char);
		else
			j++;
	}
	return (j);
}

static int	add_word(char **res, int i, char *word_start, int word_len)
{
	if (word_len < 0)
	{
		ft_putstr_fd("minishell: internal parse error\n", 2);
		return (0);
	}
	res[i] = word_dup(word_start, word_len);
	if (!res[i])
		return (0);
	return (1);
}

static char	**handle_split_error(char **result, int i)
{
	free_split_result(result, i);
	return (NULL);
}

char	**quote_safe_split(char *str)
{
	char			**res;
	t_split_data	pos;

	res = (char **)malloc(sizeof(char *) * (word_count(str) + 1));
	if (!res)
		return (NULL);
	pos.i = 0;
	pos.j = 0;
	while (str[pos.j])
	{
		pos.j = skip_whitespaces(str, pos.j);
		if (str[pos.j])
		{
			pos.start = pos.j;
			pos.end = find_word_end(str, pos.start);
			if (pos.end == -1)
				return (handle_split_error(res, pos.i));
			if (!add_word(res, pos.i, &str[pos.start], pos.end - pos.start))
				return (handle_split_error(res, pos.i));
			pos.j = pos.end;
			pos.i++;
		}
	}
	res[pos.i] = NULL;
	return (res);
}
