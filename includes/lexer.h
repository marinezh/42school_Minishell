#ifndef LEXER_H
# define LEXER_H

# define SPACING_FACTOR 4

#include "minishell.h"
// typedef struct s_cmd_input
// {
// 	char	*input;
// 	char	*spaced;
// 	int		len;
// 	int		i;
// 	int		j;
// 	// t_list  env; // need to do linkedlist part in libft
// }			t_cmd_input;

int			getpwd(void);
//char		**run_lexer(t_cmd_input *cmd);
int			read_prompt(t_cmd_input *data);
//char		*add_space(t_cmd_input *cmd);
void		add_space(t_cmd_input *cmd);
int			word_count(char *str, char delimiter);
char		*word_dup(char *str, int len);

char		**quote_safe_split(char *str, char del);
int			fmt_quotes(char *input, char *output, int *i, int *j, int copy);
int			copy_quoted_seg(char *input, char *output, int *i, int *j);
int			skip_quoted_seg(char *input, int *i);

int			is_single_op(char *input, int i);
int			is_dbl_op(char *input, int i);
int			is_triple_op(char *input, int i);

void		process_one(char *input, char *output, int *i, int *j);
void		process_two(char *input, char *output, int *i, int *j);
void		process_three(char *input, char *output, int *i, int *j);

#endif