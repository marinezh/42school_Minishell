#ifndef STRUCTS_H
# define STRUCTS_H

typedef enum e_token_type
{
	WORD,
	PIPE,
	REDIR_IN,
	REDIR_OUT,
	REDIR_APPEND,
	HEREDOC
}						t_token_type;
typedef enum e_redirection
{
	STD, // standart in/out
	REDIR_IN, 
	REDIR_OUT,
	REDIR_APPEND,
	HEREDOC
}						t_redirection;

typedef struct s_token
{
	char				*value;
	t_token_type		type;
	struct s_token		*next;
}						t_token;

// typedef struct s_command
// {
// 	char **args;            // command + arguments
// 	char *infile;           // for <
// 	char *outfile;          // for > or >>
// 	int append;             // 1 if >>, 0 if >
// 	int pipe;               // 1 if followed by |
// 	struct s_command *next; // next command in pipeline
// }						t_command;

// linked list of structs split by pipe
typedef struct s_files
{
	int	fd;
	char	*name;
	t_redirection 	red_types;  //  < << >> > 
} t_files;

typedef struct s_command
{
	int					index;
	char **args;		// command + arguments
	char *infile;		// for < or << (herdoc)
	char *outfile;		// for > or >>
	int append;			// 1 if >>, 0 if >
	int pipe;			// 1 if followed by |
	t_token				*tokens;
	t_files				**redirections;
	struct s_command	*next;
}						t_command;

// // pattens of logical command split by pipe connected in linke list
// typedef struct s_cmd_node
// {
// 	int					key;
// 	char				*value;
// 	struct s_cmd_node	*next;
// }						t_cmd_node;

typedef struct s_cmd_input
{
	char				*input;
	char				*spaced;
	int					len;
	int					i;
	int					j;
	// t_list  env; // need to do linkedlist part in libft
}						t_cmd_input;

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

#endif
