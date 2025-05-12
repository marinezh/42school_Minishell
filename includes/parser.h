#ifndef PARSER_H
# define PARSER_H

#include "minishell.h"

t_command *parse_tokens(t_token *token_list);
t_token *tokenize_input(char *input);
int error_check(t_token *token);

// DELETE LATER DEBUG PRINTING FUNCTIONS
void print_tokens(t_token *tok);
const char *token_type_to_str(t_token_type type);
void print_commands(t_command *cmd_list);

# endif