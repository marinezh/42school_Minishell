#ifndef EXPANTION_H
# define EXPANTION_H

# include "minishell.h"

int		replace_variable(t_token *token, int i, int var_len, const char *value);
int		replace_undefined_variable(t_token *token, int i, int var_len);
char	*extract_variable_name(const char *input);
int		expand_variables(t_token *token, t_data *data);
int		handle_expantion(t_token *cur, t_data *data, int *i);
char	*expand_heredoc_line(char *input, t_data *data);
int		handle_word_splitting(t_token **tokens, t_data *data);
int		should_expand_variable(const char *str, int in_single);
int		expand_heredoc_file(t_token *tokens, t_data *data);
int		handle_expantion(t_token *cur, t_data *data, int *i);
int		handle_status_var(t_token *token, int status, int *i);
int		process_expantion(t_token *token, t_data *data, int *i);
int		process_status_var(t_token *token, t_data *data, int *i);

#endif