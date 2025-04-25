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

typedef struct s_token
{
	char				*value;
	t_token_type		type;
	struct s_token		*next;
}						t_token;

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
	char        envp_f;
	// char        exit_t;
	// int         status;
};

// pattens of logical command split by pipe connected in linke list
typedef	struct s_cmd_node
{
	int	key;
	char *value;
	struct s_cmd_node	*next;
} t_cmd_node;

// linked list of structs split by pipe
typedef	struct s_command
{
	int index;
	char	**value;
	t_cmd_node *cmd_nodes;
	struct s_command *next;
} t_command;

#endif