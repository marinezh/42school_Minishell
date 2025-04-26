#ifndef PARSER_H
# define PARSER_H

t_command	*parse_tokens(char **tokens);
void print_command_debug(t_command *cmd);


# endif