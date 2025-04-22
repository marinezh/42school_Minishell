#include "lexer.h"

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
			|| (input[i] == '<' && input[i + 1] == '<')
			|| (input[i] == '&' && input[i + 1] == '&')
			|| (input[i] == '|' && input[i + 1] == '|'))
		return (1);
	return (-1);
}

int	is_triple_op(char *input, int i)
{
	if (!input[i + 1] || !input[i + 2])
		return (-1);
	if ((input[i] == '<' && input[i + 1] == '<' && input[i + 2] == '<'))
		return (1);
	return (-1);
}