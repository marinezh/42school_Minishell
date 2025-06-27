#include "minishell.h"

int	replace_variable(t_token *token, int i, int var_len, const char *value)
{
	char	*prefix;
	char	*suffix;
	char	*new_value;
	char	*final_value;

	prefix = ft_substr(token->value, 0, i);
	if (!prefix)
		return (0);
	new_value = ft_strjoin(prefix, value);
	if (!new_value)
		return (free_strings(prefix, NULL), 0);
	suffix = ft_strdup(&token->value[i + var_len + 1]);
	if (!suffix)
		return (free_strings(prefix, new_value, NULL), 0);
	final_value = ft_strjoin(new_value, suffix);
	if (!final_value)
		return (free_strings(prefix, suffix, new_value, NULL), 0);
	free(token->value);
	token->value = final_value;
	free_strings(prefix, suffix, new_value, NULL);
	return (1);
}

int	replace_undefined_variable(t_token *token, int i, int var_len)
{
	char	*prefix;
	char	*suffix;
	char	*final_value;

	prefix = ft_substr(token->value, 0, i);
	if (!prefix)
		return (0);
	suffix = ft_strdup(&token->value[i + var_len + 1]);
	if (!suffix)
		return (free_strings(prefix, NULL), 0);
	final_value = ft_strjoin(prefix, suffix);
	if (!final_value)
		return (free_strings(prefix, suffix, NULL), 0);
	free(token->value);
	token->value = final_value;
	free_strings(prefix, suffix, NULL);
	return (1);
}

char	*extract_variable_name(const char *input)
{
	int		j;
	char	*var_name;

	j = 0;
	while (input[j] && (ft_isalnum(input[j]) || input[j] == '_'))
		j++;
	var_name = ft_substr(input, 0, j);
	return (var_name);
}
void check_tokens(t_token *token)
{
	t_token *current = token;

	while (current)
	{
		if (current->type == HEREDOC && current->next)
		{
			t_token *delim = current->next;

			// ❗ Disable expansion for HEREDOCs no matter what
			delim->expantion = 0;
			if (delim->file)
				delim->file->to_expand = 0;

			printf("HEREDOC: disabling expansion for delimiter '%s'\n", delim->value);
			printf("[DEBUG] check_tokens: HEREDOC found, setting '%s' to expantion=0\n", delim->value);

		}
		else if ((current->type == WORD || current->type == FILE_NAME) && current->value)
		{
			// Normal tokens can expand variables
			current->expantion = (ft_strchr(current->value, '$') != NULL);
			if (current->file)
				current->file->to_expand = current->expantion;
		}
		current = current->next;
	}
}
// typedef struct s_token
// {
// 	t_token_type		type;
// 	char				*value;
// 	int					in_db_quotes;
// 	int					expantion;
// 	struct s_token		*prev;
// 	struct s_token		*next;
// 	struct s_files		*file;
// }						t_token;

// // osibilities for code improvement
// typedef struct s_files
// {
// 	int				fd;               // File descriptor for the opened file
// 	char			*name;           // File name or heredoc delimiter
// 	t_token_type	type;            // Type of redirection: > >> < <<
// 	int				to_expand;	// Flag to control variable expansion in heredocs
// 	struct s_files	*next; 			// Pointer to the next redirection
// }						t_files;
