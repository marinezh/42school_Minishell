/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikozhina <ikozhina@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 00:30:17 by mzhivoto          #+#    #+#             */
/*   Updated: 2025/07/15 10:34:56 by ikozhina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

void	free_tokens(t_token *tokens);
void	free_command_list(t_command *commands);
void	free_split_input(char **split);
void	free_split_result(char **result, int i);
void	free_strings(char *str, ...);
void	free_exp_parts(t_exp_parts *parts);
void	free_file_list(t_files *list);

#endif