/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikozhina <ikozhina@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 00:26:38 by mzhivoto          #+#    #+#             */
/*   Updated: 2025/07/15 10:35:49 by ikozhina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "minishell.h"

t_command	*parse_input(t_command *commands, t_data *data, char *input);
t_token		*tokenize_input(char **split_input, t_data *data);
t_command	*parse_tokens(t_token *token_list, t_data *data);
int			error_check(t_token *token, t_data *data);
int			is_redirect_type(t_token *token);
void		delete_empty_tokens(t_token **head);
void		handle_pipe(t_command *cur, t_token **token_list,
				t_command **cur_cmd);
int			handle_redirection(t_command *cur, t_token **token_list);
int			handle_word_token(t_command *cur, t_token **token_list);
char		**realloc_args(char **args, int count, char *value);
void		append_to_list(t_files **list, t_files *node);
int			add_redirection(t_command *cmd, char *filename, int type);
int			remove_quotes_from_command_args(t_command *commands, t_data *data);

#endif