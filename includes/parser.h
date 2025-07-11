#ifndef PARSER_H
# define PARSER_H

#include "minishell.h"

t_command *parse_tokens(t_token *token_list);
t_token *tokenize_input(char **split_input);
//int error_check(t_token *token);
int error_check(t_token *token, t_data *data);
//t_files *parse_redir(t_token *token_list);

char	**realloc_args(char **args, int count, char *value);
void handle_pipe(t_command *current, t_token **token_list,t_command **current_cmd);
int handle_redirection(t_command *current, t_token **token_list);
int handle_word_token(t_command *current, t_token **token_list);
void	add_redirection(t_command *cmd, char *filename, int type);
t_files	*create_file_node(char *name, int type);
int	is_redirect_type(t_token *token);
//void expand_variables(t_token *token, t_data *data);
//void remove_outer_quotes(t_token *token);
//void replace_undefined_variable(t_token *token, int i, int var_len);
//void replace_variable(t_token *token, int i, int var_len, const char *value);
//void handle_status_var(t_token *token, int status, int *i);
//void handle_expantion(t_token *token, t_data *data, int *i);
//char *extract_variable_name(const char *input);
void remove_outer_quotes_from_string(char *str);
void remove_quotes_from_command_args(t_command *commands);
void remove_quotes_from_files(t_files *files);

char *expand_heredoc_line(char *input, t_data *data);
//void replace_current_with_multiple(t_token **current, t_token *new_tokens);
//t_token *create_token_list_from_split(char **split, int type);
//t_token *create_token_list_from_split(char **split);
//t_token *handle_word_splitting(t_token *tokens);

// DELETE LATER DEBUG PRINTING FUNCTIONS
void print_tokens(t_token *tok);
const char *token_type_to_str(t_token_type type);
void print_commands(t_command *cmd_list);
void print_files_nodes(t_files *files);

# endif