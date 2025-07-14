/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhivoto <mzhivoto@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 00:26:05 by mzhivoto          #+#    #+#             */
/*   Updated: 2025/07/15 00:26:11 by mzhivoto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "minishell.h"

char	**preprocess_input(char *input, t_data *data);
int		word_count(char *str);
char	*word_dup(char *str, int len);
int		is_whitespace(char c);
int		skip_whitespaces(char *str, int j);
char	**quote_safe_split(char *str);
int		is_single_op(char *input, int i);
int		is_dbl_op(char *input, int i);
void	process_one(char *input, char *output, int *i, int *j);
void	process_two(char *input, char *output, int *i, int *j);

#endif