#include <minishell.h>

int	copy_quoted_seg(char *input, char *output, int *i, int *j)
{
	char quote; 
	
	quote = input[*i]; 
	output[*j] = input[*i]; // copy openning quotes
	(*i)++;
	(*j)++;
	while (input[*i] && input[*i] != quote) // copy everything in qutes
	{
		output[*j] = input[*i];
		(*i)++;
		(*j)++;
	}
	if (input[*i] != quote)
	{
		ft_putstr_fd("minishell:quotes are not closed", 2);
		//ft_putstr_fd(ERR_QUOTES, 2);
		return (ERR_PARSER);
	}
	output[*j] = input[*i]; // copy closing quotes
	(*i)++;
	(*j)++;
	return (0);
}

int skip_quoted_seg(char *input, int *i)
{
	char quote; 
	
	quote = input[*i];
	(*i)++; // skip openning quote
	while (input[*i] && input[*i] != quote)
		(*i)++;
	if (!input[*i])
	{
		ft_putstr_fd("minishell:quotes are not closed", 2);
		//ft_putstr_fd(ERR_QUOTES, 2);
		return (-1);
	}
	(*i)++; // skip closing quote
	return (0);
}

void	error_msg(char *msg)
{
	ft_putendl_fd(msg, 2);
}