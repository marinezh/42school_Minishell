#include <minishell.h>

t_command *create_new_command(int index)
{
	t_command *cmd = malloc(sizeof(t_command));
	if (!cmd)
		return NULL;
	cmd->index = index;
	cmd->args = NULL;
	cmd->tokens = NULL;
	cmd->next = NULL;
	return cmd;
}

void append_token(t_token **head, t_token *token)
{
	t_token *copy = malloc(sizeof(t_token));
	if (!copy)
		return;
	copy->type = token->type;
	copy->value = strdup(token->value);
	copy->next = NULL;

	if (!*head)
		*head = copy;
	else
	{
		t_token *curr = *head;
		while (curr->next)
			curr = curr->next;
		curr->next = copy;
	}
}

char **realloc_args(char **args, int count, char *value)
{
	int i = 0;

	char **new_args = malloc(sizeof(char *) * (count + 2));
	if (!new_args)
		return NULL;
	while (i < count)
	{
		new_args[i] = args[i];
		i++;
	}
	new_args[count] = strdup(value);
	new_args[count + 1] = NULL;
	free(args);
	return new_args;
}

t_command *parse_tokens(t_token *token_list)
{
	t_command *head = NULL; 
	t_command *tail = NULL;
	t_command *current = NULL;
	int command_index = 0;

	while (token_list)
	{
		if (!current) // On PIPE, start a new command
		{
			current = create_new_command(command_index++);
			if (!head)
				head = current;
			if (tail)
				tail->next = current;
			tail = current;
		}
		if (token_list->type == PIPE)
		{
			append_token(&current->tokens, token_list);
			current = NULL;
			token_list = token_list->next;
			continue;
		}
		append_token(&current->tokens, token_list); // Add token to current command
		if (token_list->type == WORD) // If it's a WORD, add to args
		{
			int argc = 0;
			while (current->args && current->args[argc])
				argc++;
			current->args = realloc_args(current->args, argc, token_list->value);
		}
		token_list = token_list->next;
	}
	return head;
}
