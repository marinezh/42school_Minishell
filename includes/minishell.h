/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhivoto <mzhivoto@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 13:20:43 by mzhivoto          #+#    #+#             */
/*   Updated: 2025/04/17 19:12:09 by mzhivoto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <limits.h>
# include <stdio.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

# define RESET "\033[0m"
# define BLACK "\033[30m"
# define RED "\033[31m"
# define GREEN "\033[32m"
# define YELLOW "\033[33m"
# define BLUE "\033[34m"
# define MAGENTA "\033[35m"
# define CYAN "\033[36m"
# define WHITE "\033[37m"
# define BOLD "\033[1m"
# define PROMPT "\001" GREEN BOLD "\002minishell$ \001" RESET "\002"

typedef struct s_data
{
	char	*input;
	int		len;
	// t_list  env; // need to do linkedlist part in libft

}			t_data;

int			getpwd(void);
int			parsing(t_data *data);
int			print_prompt(t_data *data);
// char	**ft_split_2(char *str);
char		**ft_split_2(char *str, char delimiter);
int			process_quotes(char *input, char *output, int *i, int *j, int copy);

#endif
