int	handle_quotes(char *input, char *new_input, int *i, int *j)
{
	char	quote;

	quote = input[*i];
	new_input[*j] = input[*i];
	(*j)++;
	(*i)++;
	while (input[*i] && input[*i] != quote)
	{
		new_input[*j] = input[*i];
		(*j)++;
		(*i)++;
	}
	if (input[*i] != quote)
	{
		printf("quotes not closed\n");
		return (-1);
	}
	new_input[*j] = input[*i];
	(*j)++;
	(*i)++;
	return (0);
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