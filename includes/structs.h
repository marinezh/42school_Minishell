#ifndef STRUCTS_H
# define STRUCTS_H

typedef enum e_token_type
{
	NONE,         // 0
	WORD,         // 1
	PIPE,         // 2
	REDIR_OUT,    // 3 >
	REDIR_APPEND, // 4 >>
	REDIR_IN,     // 5 <
	HEREDOC,      // 6 <<
	FILE_NAME     // 7
}						t_token_type;

typedef enum e_error_code
{
	ERR_GENERIC = 1,
	ERR_INVALID_OPTION = 2,
	ERR_PERM_DENIED = 126,
	ERR_CMD_NOT_FOUND = 127,
	ERR_INTERUPTED_SIGINT = 130,
	ERR_INVALID_EXIT_CODE = 255,
}						t_error_code;

typedef struct s_cmd_input
{
	char				*input;
	char				*spaced;
	int					len;
	// int					i;
	// int					j;
}						t_cmd_input;

typedef struct s_token
{
	t_token_type		type;
	char				*value;
	struct s_token		*prev;
	struct s_token		*next;
}						t_token;

// osibilities for code improvement
typedef struct s_files
{
	char *name;           // File name or heredoc delimiter
	int type;             // Type of redirection: > >> < <<
	int fd;               // File descriptor for the opened file
	struct s_files *next; // Pointer to the next redirection
}						t_files;

// linked list of structs split by pipe
typedef struct s_command
{
	int					index;
	char **args;     // command + arguments
	t_token *tokens; // Should we delete this from t_command?
	t_files *in;     // list of << and <
	t_files *out;    // list of out > or >>
	int					pipe;
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
	char				exit_f;
	int					status;
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
