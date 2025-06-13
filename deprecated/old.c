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
// void handle_pipe(t_command *current, t_token **token_list,
// 					t_command **current_cmd)
// {
// 	current->pipe = 1;
// 	*current_cmd = NULL;
// 	*token_list = (*token_list)->next;
// }
// int handle_redirection(t_command *current, t_token **token_list)
// {
// 	int redir_type;
	
// 	redir_type = (*token_list)->type;
// 	*token_list = (*token_list)->next;
	
// 	if (*token_list && ((*token_list)->type == WORD || (*token_list)->type == FILE_NAME))
// 	{
// 		add_redirection(current, (*token_list)->value, redir_type);
// 		*token_list = (*token_list)->next;
// 		return (1);
// 	}
// 	return (0);
// }

// int handle_word_token(t_command *current, t_token **token_list)
// {
// 	int argc;
	
// 	argc = 0;
// 	while (current->args && current->args[argc])
// 		argc++;
// 	current->args = realloc_args(current->args, argc, (*token_list)->value);
// 	if (!current->args)
// 		return (0);
// 	*token_list = (*token_list)->next;
// 	return (1);
// }