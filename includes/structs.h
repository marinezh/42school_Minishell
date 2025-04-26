#ifndef INIT_H
# define INIT_H

typedef enum e_token_type
{
	WORD,
	PIPE,
	REDIR_IN,
	REDIR_OUT,
	REDIR_APPEND,
	HEREDOC
}					t_token_type;

typedef struct s_token
{
	char			*value;
	t_token_type	type;
	struct s_token	*next;
}					t_token;

typedef struct s_command
{
	char				**args;			// command + arguments
	char				*infile;		// for <
	char				*outfile;		// for > or >>
	int					append;			// 1 if >>, 0 if >
	int					pipe;			// 1 if followed by |
	struct s_command	*next;			// next command in pipeline
}			t_command;

typedef struct s_cmd_input
{
	char			*input;
	char			*spaced;
	int				len;
	int				i;
	int				j;
	// t_list  env; // need to do linkedlist part in libft
}					t_cmd_input;

#endif
