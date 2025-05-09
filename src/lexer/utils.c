#include <minishell.h>

int	fmt_quotes(char *input, char *output, int *i, int *j, int copy)
{
	char quote; 
	
	quote = input[*i]; 
	if (copy && output) 
		output[*j] = input[*i];
	(*i)++; 
	if (copy && output)
		(*j)++; 
	while (input[*i] && input[*i] != quote)
	{
		if (copy && output)
			output[*j] = input[*i];
		(*i)++;
		if (copy && output)
			(*j)++;
	}
	if (input[*i] != quote)
	{
		printf("quotes not closed\n");
		return (-1);
	}
	if (copy && output)
		output[*j] = input[*i];
	(*i)++;
	if (copy && output)
		(*j)++;
	return (0);
}

void	error_msg(char *msg)
{
	ft_putendl_fd(msg, 2);
}