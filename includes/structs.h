#ifndef STRUCTS_H
# define STRUCTS_H

// declaration of main exection struct
typedef struct s_data	t_data;
// function pointer type declaration
typedef int				(*t_bltin)(t_data);

// struct for one environment variable (as linked list)
typedef struct s_env
{
	char				*key;
	char				*value;
	struct s_env		*next;
}						t_env;

// main data struct for execution
struct					s_data
{
	char				*cmd_names[7];
	t_bltin				builtins[7];
	char				**envp;
	t_env				*envp_list;
	char				envp_f;
	// char        exit_t;
	// int         status;
};

typedef enum e_token_type
{
	WORD,
	PIPE,
	REDIR_OUT, // >
	REDIR_APPEND, // >>
	REDIR_IN, // <
	HEREDOC // <<
}						t_token_type;

typedef struct s_token
{
	t_token_type		type;
	char				*value;
	struct s_token		*next;
}						t_token;

// typedef struct s_files
// {
// 	int	fd;
// 	char	*name;
// 	t_redirection 	red_types;  //  < << >> > 
// } t_files;

// linked list of structs split by pipe
typedef struct s_command
{
	int					index;
	char **args;		// command + arguments
	char *infile;		// for < or << (herdoc)
	char *outfile;		// for > or >>
	int append;			// 1 if >>, 0 if >
	int pipe;			// 1 if followed by |
	t_token				*tokens; // linked list of tokens
	//t_files				**redirections;
	//t_files				in; // name of last in including << and <
	//t_files				out;// name of last out > or >>
	struct s_command	*next;
}						t_command;

typedef struct s_cmd_input
{
	char				*input;
	char				*spaced;
	int					len;
	int					i;
	int					j;
	// t_list  env; // need to do linkedlist part in libft
}						t_cmd_input;



#endif
