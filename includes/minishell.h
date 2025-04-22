#ifndef MINISHELL_H
# define MINISHELL_H


# include "structs.h"
# include "lexer.h"
# include "libft.h"
# include <limits.h>
# include <stdio.h>
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



#endif
