#ifndef PARSER_H
# define PARSER_H

#include "minishell.h"
//t_command	*parse_tokens(char **tokens);
//t_command *parse_tokens(t_token *tokens);
t_command *parse_tokens(t_token *token_list);
void print_command_debug(t_command *cmd);
//t_token *tokenize_input(char *input);
//t_token *tokenize_input( t_cmd_input cmd);
void print_tokens(t_token *tokens);
const char *token_type_to_str(t_token_type type);
void print_commands(t_command *cmd_list);

t_token *tokenize_input(char *input);
int error_check(t_token *token);


# endif