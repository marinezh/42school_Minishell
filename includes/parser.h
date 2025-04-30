#ifndef PARSER_H
# define PARSER_H

//t_command	*parse_tokens(char **tokens);
t_command *parse_tokens(t_token *tokens);
void print_command_debug(t_command *cmd);
t_token *tokenize_input(char *input);
//t_token *tokenize_input( t_cmd_input cmd);
void print_tokens(t_token *tokens);

# endif