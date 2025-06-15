#ifndef PARSER_H
# define PARSER_H

#include "minishell.h"

t_command *parse_tokens(t_token *token_list);
t_token *tokenize_input(char **split_input);
//int error_check(t_token *token);
int error_check(t_token *token, t_data *data);
//t_files *parse_redir(t_token *token_list);
char **preprocess_input(char *input);
char	**realloc_args(char **args, int count, char *value);
void handle_pipe(t_command *current, t_token **token_list,t_command **current_cmd);
int handle_redirection(t_command *current, t_token **token_list);
int handle_word_token(t_command *current, t_token **token_list);
void	add_redirection(t_command *cmd, char *filename, int type);
t_files	*create_file_node(char *name, int type);
void expand_variables(t_token *token, t_data *data);
void remove_outer_quotes(t_token *token);

// DELETE LATER DEBUG PRINTING FUNCTIONS
void print_tokens(t_token *tok);
const char *token_type_to_str(t_token_type type);
void print_commands(t_command *cmd_list);
void print_files_nodes(t_files *files);

# endif