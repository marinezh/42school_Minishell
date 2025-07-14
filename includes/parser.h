/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhivoto <mzhivoto@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 00:26:38 by mzhivoto          #+#    #+#             */
/*   Updated: 2025/07/15 00:34:26 by mzhivoto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "minishell.h"

t_command	*parse_input(t_command *commands, t_data *data, char *input);
t_token		*tokenize_input(char **split_input, t_data *data);
t_command	*parse_tokens(t_token *token_list, t_data *data);
int			error_check(t_token *token, t_data *data);
// utils
int			is_redirect_type(t_token *token);
void		delete_empty_tokens(t_token **head);
// parser_handlers
void		handle_pipe(t_command *cur, t_token **token_list, t_command **cur_cmd);
int			handle_redirection(t_command *cur, t_token **token_list);
int			handle_word_token(t_command *cur, t_token **token_list);
char		**realloc_args(char **args, int count, char *value);
void		append_to_list(t_files **list, t_files *node);

int			add_redirection(t_command *cmd, char *filename, int type);
int			remove_quotes_from_command_args(t_command *commands, t_data *data);

// DELETE LATER DEBUG PRINTING FUNCTIONS
// void		print_tokens(t_token *tok);
// const char	*token_type_to_str(t_token_type type);
// void		print_commands(t_command *cmd_list);
// void		print_files_nodes(t_files *files);

#endif