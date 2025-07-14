/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhivoto <mzhivoto@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 00:26:27 by mzhivoto          #+#    #+#             */
/*   Updated: 2025/07/15 00:26:31 by mzhivoto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define _POSIX_C_SOURCE 200809L
# include <signal.h>
# include "structs.h"
# include "lexer.h"
# include "parser.h"
# include "utils.h"
# include "libft.h"
# include "exec.h"
# include "expantion.h"
# include "error_messages.h"
# include <limits.h>
# include <stdio.h>
# include <stdio.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <errno.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <dirent.h>
#include <termios.h>
#include <sys/ioctl.h>

#endif
