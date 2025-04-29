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
// t_command	*parse_tokens(char **tokens)
// {
// 	t_command	*head = init_command();
// 	t_command	*current = head;
// 	int			i = 0;
// 	int 		j = 0;
// 	int			count;

// 	while (tokens[i])
// 	{
// 		if (strcmp(tokens[i], "|") == 0)
// 		{
// 			current->pipe = 1;
// 			current->next = init_command();
// 			current = current->next; // add if current->next  == NULL
// 			i++;
// 		}
// 		else if (strcmp(tokens[i], "<") == 0)
// 		{
// 			i++;
// 			current->infile = ft_strdup(tokens[i++]);
// 		}
// 		else if (strcmp(tokens[i], ">") == 0 || strcmp(tokens[i], ">>") == 0)
// 		{
// 			current->append = strcmp(tokens[i], ">>") == 0;
// 			i++;
// 			current->outfile = ft_strdup(tokens[i++]);
// 		}
// 		else
// 		{
// 			// Add token to args list
// 			count = 0;
// 			while (current->args && current->args[count])
// 				count++;
// 			char **new_args = malloc(sizeof(char *) * (count + 2));
// 			j = 0;
// 			while(j < count)
// 			{
// 				new_args[j] = current->args[j];
// 				j++;
// 			}
// 			new_args[count] = ft_strdup(tokens[i++]);
// 			new_args[count + 1] = NULL;
// 			free(current->args);
// 			current->args = new_args;
// 		}
// 	}
// 	return (head);
// }