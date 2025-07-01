#ifndef LEXER_H
# define LEXER_H

# define SPACING_FACTOR 4
# define QUOTE_ERROR_PTR ((char **)(-2))

#include "minishell.h"



int			getpwd(void);
//char		**run_lexer(t_cmd_input *cmd);
int			read_prompt(t_cmd_input *data);
//char		*add_space(t_cmd_input *cmd);
char		**preprocess_input(char *input, t_data *data);
char		*add_space(t_cmd_input *cmd, t_data *data);
int			word_count(char *str);
char		*word_dup(char *str, int len);
int			is_whitespace(char c);

char		**quote_safe_split(char *str);
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