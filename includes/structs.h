/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhivoto <mzhivoto@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 00:27:25 by mzhivoto          #+#    #+#             */
/*   Updated: 2025/07/15 10:53:05 by mzhivoto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

extern volatile sig_atomic_t	g_sig_received;
extern int						rl_done;

typedef enum e_token_type
{
	NONE,
	WORD,
	PIPE,
	REDIR_OUT,
	REDIR_APPEND,
	REDIR_IN,
	HEREDOC,
	FILE_NAME
}								t_token_type;

typedef enum e_error_code
{
	ERR_GENERIC = 1,
	ERR_PARSER = 2,
	ERR_PERM_DENIED = 126,
	ERR_CMD_NOT_FOUND = 127,
	ERR_INTERUPTED_SIGINT = 130,
	ERR_INVALID_EXIT_CODE = 2,
}								t_error_code;

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
	int							i;
	int							j;
	char						*temp;
	char						*str;
	char						in_quote;
}								t_qts_proc;

typedef struct s_token
{
	t_token_type				type;
	char						*value;
	int							in_db_quotes;
	struct s_token				*prev;
	struct s_token				*next;
}								t_token;

typedef struct s_files
{
	int							fd;
	char						*name;
	t_token_type				type;
	int							to_expand;
	struct s_files				*next;
}								t_files;

typedef struct s_command
{
	int							index;
	char						**args;
	t_files						*in;
	t_files						*out;
	t_files						*redirections;
	int							pipe;
	struct s_command			*next;
}								t_command;

typedef struct s_cmd_chain
{
	t_command					*head;
	t_command					*tail;
	int							cmd_index;
}								t_cmd_chain;

typedef struct s_data			t_data;
typedef int						(*t_bltin)(t_data *, t_command *);
typedef struct s_exp_params
{
	t_token						*token;
	int							*index;
	t_data						*data;
	char						*var_name;
}								t_exp_params;

typedef struct s_exp_state
{
	int							in_single;
	int							in_double;
	int							in_dollar_quote;
	int							i;
}								t_exp_state;

typedef struct s_env
{
	char						*key;
	char						*value;
	struct s_env				*next;
}								t_env;

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

typedef struct s_token_connection
{
	t_token						**tokens_head;
	t_token						*prev;
	t_token						*new_tokens;
	t_token						*next;
	t_token						*current;
}								t_token_connection;

typedef struct s_split_data
{
	char						**result;
	int							i;
	int							j;
	int							start;
	int							end;
}								t_split_data;

typedef struct s_splitted_tok
{
	t_token						*head;
	t_token						*last;
	t_token						*new;
}								t_splitted_tok;

typedef struct s_splitted_word
{
	t_token						*cur;
	t_token						*prev;
	t_token						*next;
	t_token						*last;
}								t_splitted_word;

typedef struct s_pipe
{
	t_command					*cur_cmd;
	int							cmd_count;
	int							in_pipe[2];
	int							cur_pipe[2];
}								t_pipe;

#endif
