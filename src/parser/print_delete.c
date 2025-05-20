#include "minishell.h"

// void	print_command_debug(t_command *cmd)
// {
// 	int i;

// 	i = 0;
// 	printf("====== COMMAND ======\n");
// 	printf("index is %d\n", cmd->index);
// 	if (cmd->args)
// 	{
// 		printf("Args: ");
// 		while (cmd->args[i])
// 		{
// 			printf("'%s' ", cmd->args[i]);
// 			i++;
// 		}
// 		printf("\n");
// 	}
// 	if (cmd->infile)
// 		printf("Infile: %s\n", cmd->infile);
// 	if (cmd->outfile)
// 		printf("Outfile: %s (append: %d)\n", cmd->outfile, cmd->append);
// 	if (cmd->pipe)
// 		printf("Pipe to next: yes\n");
// 	printf("=====================\n");
// }

// void print_tokens(t_token *tokens)
// {
// 	while (tokens != NULL)
// 	{
// 		switch (tokens->type)
// 		{
// 			case WORD:
// 				printf("WORD: %s\n", tokens->value);
// 				break ;
// 			case PIPE:
// 				printf("PIPE: %s\n", tokens->value);
// 				break ;
// 			case REDIR_IN:
// 				printf("REDIR_IN: %s\n", tokens->value);
// 				break ;
// 			case REDIR_OUT:
// 				printf("REDIR_OUT: %s\n", tokens->value);
// 				break ;
// 			case REDIR_APPEND:
// 				printf("REDIR_APPEND: %s\n", tokens->value);
// 				break ;
// 			case HEREDOC:
// 				printf("HEREDOC: %s\n", tokens->value);
// 				break ;
// 			default:
// 				printf("Unknown token type\n");
// 				break ;
// 		}
// 		tokens = tokens->next;  // Move to the next token in the linked list
// 	}
// }
void	print_tokens(t_token *tok)
{
	while (tok)
	{
		printf("       [%d] %s\n", tok->type, tok->value);
		tok = tok->next;
	}
}
// const char *token_type_to_str(t_token_type type)
// {
// 	switch (type) {
// 		case WORD: return ("WORD");
// 		case PIPE: return ("PIPE");
// 		case REDIR_OUT: return ("REDIR_OUT");
// 		case REDIR_APPEND: return ("REDIR_APPEND");
// 		case REDIR_IN: return ("REDIR_IN");
// 		case HEREDOC: return ("HEREDOC");
// 		case FILE_NAME : return ("FILE_NAME");
// 		default: return ("UNKNOWN");
// 	}
// }

// void print_commands(t_command *cmd_list)
// {
// 	while (cmd_list)
// 	{
// 		printf("Command #%d:\n", cmd_list->index);
// 		printf("  Args: ");
// 		if (cmd_list->args)
// 		{
// 			for (int i = 0; cmd_list->args[i]; i++)
// 				printf("\"%s\" ", cmd_list->args[i]);
// 		}
// 		else
// 			printf("(none)");
// 		printf("\n");
// 		// Print tokens
// 		printf("  Tokens:\n");
// 		t_token *tok = cmd_list->tokens;
// 		while (tok)
// 		{
// 			printf("       [%s] %s\n", token_type_to_str(tok->type),
// tok->value);
// 			tok = tok->next;
// 		}
// 		cmd_list = cmd_list->next;

// 		printf("=====================\n");
// 	}
// }
void	print_files_nodes(t_files *files)
{
	while (files)
	{
		printf("File name %s, file_type %d\n", files->name, files->type);
		files = files->next;
	}
}
const char	*token_type_to_str(t_token_type type)
{
	switch (type)
	{
	case WORD:
		return ("WORD");
	case PIPE:
		return ("PIPE");
	case REDIR_OUT:
		return ("REDIR_OUT");
	case REDIR_APPEND:
		return ("REDIR_APPEND");
	case REDIR_IN:
		return ("REDIR_IN");
	case HEREDOC:
		return ("HEREDOC");
	case FILE_NAME:
		return ("FILE_NAME");
	default:
		return ("UNKNOWN");
	}
}

// void	print_commands(t_command *cmd_list)
// {
// 	t_token	*tok;

// 	while (cmd_list)
// 	{
// 		printf("Command #%d:\n", cmd_list->index);
// 		printf("  Args: ");
// 		if (cmd_list->args)
// 		{
// 			for (int i = 0; cmd_list->args[i]; i++)
// 				printf("\"%s\" ", cmd_list->args[i]);
// 		}
// 		else
// 			printf("(none)");
// 		printf("\n");
// 		// Print tokens
// 		printf("  Tokens:\n");
// 		tok = cmd_list->tokens;
// 		while (tok)
// 		{
// 			printf("       [%s] %s\n", token_type_to_str(tok->type),
// 				tok->value);
// 			tok = tok->next;
// 		}
// 		cmd_list = cmd_list->next;
// 		printf("=====================\n");
// 	}
// }
void	print_commands(t_command *cmd_list)
{
	t_token *tok;
	t_files *file;

	while (cmd_list)
	{
		printf("Command #%d:\n", cmd_list->index);
		printf("  Args: ");
		if (cmd_list->args)
		{
			for (int i = 0; cmd_list->args[i]; i++)
				printf("\"%s\" ", cmd_list->args[i]);
		}
		else
			printf("(none)");
		printf("\n");
		// Print input redirections
		printf("  Input redirections:\n");
		file = cmd_list->in;
		while (file)
		{
			printf("    Type: %s, Name: \"%s\"\n",
				file->type == REDIR_IN ? "REDIR_IN" : "HEREDOC", file->name);
			file = file->next;
		}
		// Print output redirections
		printf("  Output redirections:\n");
		file = cmd_list->out;
		while (file)
		{
			printf("    Type: %s, Name: \"%s\"\n",
				file->type == REDIR_OUT ? "REDIR_OUT" : "REDIR_APPEND",
				file->name);
			file = file->next;
		}
		// Print tokens
		printf("  Tokens:\n");
		tok = cmd_list->tokens;
		while (tok)
		{
			printf("       [%s] %s\n", token_type_to_str(tok->type),
				tok->value);
			tok = tok->next;
		}
		printf("  Pipe: %s\n", cmd_list->pipe ? "Yes" : "No");
		cmd_list = cmd_list->next;
		printf("=====================\n");
	}
}