
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
		ft_putstr_fd("minishell:quotes are not closed", 2);
		//ft_putstr_fd(ERR_QUOTES, 2);
		return (ERR_PARSER);
	}
	if (copy && output)
		output[*j] = input[*i];
	(*i)++;
	if (copy && output)
		(*j)++;
	return (0);
}