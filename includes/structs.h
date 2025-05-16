#ifndef STRUCTS_H
# define STRUCTS_H

typedef enum e_token_type
{
	NONE,					// 0
	WORD,					// 1
	PIPE,					// 2
	REDIR_OUT,    // >		// 3
	REDIR_APPEND, // >>		// 4
	REDIR_IN,     // <		// 5
	HEREDOC       // <<		// 6
}						t_token_type;

typedef	enum e_error_code
{
	ERROR_GENERIC = 1,
    ERROR_INVALID_OPTION = 2,
    ERROR_MALLOC_FAILS = 12,
    ERROR_ISDIR = 126,
    ERROR_CMD_NOT_FOUND = 127,
    ERROR_INTERUPTED_SIGINT = 130,
    ERROR_INVALID_EXIT_CODE = 255,
    ERROR_SYNTAX_HEREDOC = 258,
    ERROR_IGNORE = 1024
}	t_error_code;

typedef struct s_cmd_input
{
	char				*input;
	char				*spaced;
	int					len;
	//int					i;
	//int					j;
}						t_cmd_input;

typedef struct s_token
{
	t_token_type		type;
	char				*value;

	// struct s_token		*prev;
	struct s_token		*next;
}						t_token;

//osibilities for code improvement
typedef struct s_files
{
	char *name; // File name or heredoc delimiter
	int type;   // Type of redirection: REDIR_IN, HEREDOC, REDIR_OUT, APPEND
	int fd;               // File descriptor for the opened file
	struct s_files *next; // Pointer to the next redirection
} t_files;

// linked list of structs split by pipe
typedef struct s_command
{
	int					index;
	char **args; // command + arguments
	t_token *tokens; // linked list of tokens
	// t_files				**redirections;
	t_files				in; // name of last in including << and <
	t_files				out;// name of last out > or >>
	struct s_command	*next;
}						t_command;

// declaration of main exection struct
typedef struct s_data	t_data;
// function pointer type declaration
typedef int				(*t_bltin)(t_data *, t_command *);

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



// typedef struct s_command
// {
// 	int					index;
// 	char **args;            // Command + arguments
// 	t_files *redirections;       // Linked list of redirections (<, <<, >, >>)
// 	t_token *tokens; // linked list of tokens
// 	struct s_command *next; // Pointer to the next command
// }						t_command;


