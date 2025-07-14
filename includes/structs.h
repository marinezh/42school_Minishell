#ifndef STRUCTS_H
# define STRUCTS_H

extern volatile sig_atomic_t	g_sig_received;
extern int						rl_done;

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
}								t_token_type;

typedef enum e_error_code
{
	ERR_GENERIC = 1,
	ERR_PARSER = 2,
	ERR_PERM_DENIED = 126,
	ERR_CMD_NOT_FOUND = 127,
	ERR_INTERUPTED_SIGINT = 130,
	//ERR_INVALID_EXIT_CODE = 255,
	ERR_INVALID_EXIT_CODE = 2,
	ERR_AMB_RED = 1,
   // ERR_PARSER_MEMORY = 12,		// Memory allocation failure during parsing DOUBLE CHECK
}						t_error_code;

typedef struct s_cmd_input
{
	char						*input;
	char						*spaced;
	int							len;
	int							i;
	int							j;
}								t_cmd_input;



typedef struct s_qts_proc
{
	int i;
	int j;
	char	*temp;
	char	*str;
	char	in_quote;
}	t_qts_proc;

typedef struct s_token
{
	t_token_type				type;
	char						*value;
	int							in_db_quotes;
	struct s_token				*prev;
	struct s_token				*next;
}								t_token;

// osibilities for code improvement
typedef struct s_files
{
	int fd;               // File descriptor for the opened file
	char *name;           // File name or heredoc delimiter
	t_token_type type;    // Type of redirection: > >> < <<
	int to_expand;        // Flag to control variable expansion in heredocs
	struct s_files *next; // Pointer to the next redirection
}								t_files;

// linked list of structs split by pipe
typedef struct s_command
{
	int							index;
	char						**args;
	t_files						*in;
	t_files						*out;
	t_files						*redirections; // think about creation arr of pointers
	int							pipe;
	struct s_command			*next;
}								t_command;

typedef struct s_cmd_chain
{
    t_command   *head;
    t_command   *tail;
    int         cmd_index;
} t_cmd_chain;

// Structure to group expansion parameters


// declaration of main exection struct
typedef struct s_data			t_data;
// function pointer type declaration
typedef int						(*t_bltin)(t_data *, t_command *);
typedef struct s_exp_params
{
    t_token *token;      // Current token
    int *index;          // Position in the token
    t_data *data;        // Data structure
    char *var_name;      // Variable name
} t_exp_params;

// Structure to hold expansion state
typedef struct s_exp_state
{
    int in_single;
    int in_double;
    int in_dollar_quote;
    int i;
} t_exp_state;
// struct for one environment variable (as linked list)
typedef struct s_env
{
	char						*key;
	char						*value;
	struct s_env				*next;
}								t_env;

// main data struct for execution
struct							s_data
{
	char						*cmd_names[7];
	t_bltin						builtins[7];
	char						**envp;
	t_env						*envp_list;
	char						envp_f;
	char						exit_f;
	int							status;
	int							is_pipe;
	pid_t						*pids;
};

typedef struct s_exp_parts
{
	char						*status_str;
	char						*prefix;
	char						*suffix;
	char						*new_value;
	char						*final_value;
}								t_exp_parts;

// Structure to hold token connection parameters
typedef struct s_token_connection
{
    t_token **tokens_head;  // Pointer to the head of tokens list
    t_token *prev;          // Previous token
    t_token *new_tokens;    // New tokens to connect
    t_token *next;          // Next token
    t_token *current;       // Current token to replace
} t_token_connection;

// typedef struct s_word_pos
// {
//     int start;
//     int end;
// } t_word_pos;

// Define a struct for position tracking
typedef struct s_split_data
{
	char						**result;
	int i;     // Current position in result array
	int j;     // Current position in input string
	int start; // Start position of current word
	int end;   // End position of current word
}								t_split_data;

typedef struct s_pipe
{
	t_command					*cur_cmd;
	int							cmd_count;
	int							in_pipe[2];
	int							cur_pipe[2];
}								t_pipe;

#endif


