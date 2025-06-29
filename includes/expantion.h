#ifndef EXPANTION_H
# define EXPANTION_H

#include "minishell.h"

//int	expand_variables(t_token *token, t_data *data);
int	replace_variable(t_token *token, int i, int var_len, const char *value);
int	replace_undefined_variable(t_token *token, int i, int var_len);
char	*extract_variable_name(const char *input);
//int expand_variables_her(t_token *token, t_data *data);
int expand_variables(t_token *token, t_data *data, int skip_after_heredoc);

t_token	*handle_word_splitting(t_token *tokens);
void delete_empty_tokens(t_token **head);

#endif