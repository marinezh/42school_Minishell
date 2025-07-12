#include "minishell.h"

int	is_single_op(char *input, int i)
{
	if (input[i] == '|' || input[i] == '&' || input[i] == '<'
		|| input[i] == '>')
		return (1);
	return (-1);
}

int	is_dbl_op(char *input, int i)
{
	if (!input[i + 1])
		return (-1);
	if ((input[i] == '>' && input[i + 1] == '>')
		|| (input[i] == '<' && input[i + 1] == '<'))
		return (1);
	return (-1);
}

int is_question_mark(char *input, int i)
{
	if (input[i] != '?')
		return (0);

	// Don't split if part of `$?`
	if (i > 0 && input[i - 1] == '$')
		return (0);

	// Don't split if preceded by an alphanumeric (part of a word)
	if (i > 0 && (ft_isalnum(input[i - 1]) || input[i - 1] == '_'))
		return (0);

	return (1);
}


void	process_one(char *input, char *output, int *i, int *j)
{
	output[(*j)++] = ' ';
	output[(*j)++] = input[*i];
	output[(*j)++] = ' ';
	(*i)++;
}

void	process_two(char *input, char *output, int *i, int *j)
{
	output[(*j)++] = ' ';
	output[(*j)++] = input[*i];
	output[(*j)++] = input[*i + 1];
	output[(*j)++] = ' ';
	(*i) += 2;
}
