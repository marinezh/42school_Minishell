#ifndef EXEC_H
# define EXEC_H

void	init_data(t_data *data, char **env);
int		ft_pwd(t_data *data, t_command *cmd);
int		ft_echo(t_data *data, t_command *cmd);
int		ft_env(t_data *data, t_command *cmd);
int		ft_export(t_data *data, t_command *cmd);
int		ft_unset(t_data *data, t_command *cmd);
int		ft_cd(t_data *data, t_command *cmd);
int		ft_exit(t_data *data, t_command *cmd);
void	free_double_array(char **envp);
void	free_env_list(t_env **env);
void	update_envp_array(t_data *data, t_env *envp_list);
void	node_add_last(t_env **envp_list, t_env *new_node);
t_env	*create_env_node(char *str);
int		env_list_size(t_env *env);
int		print_current_envp(t_data *data, t_command *cmd);
int		var_name_len(char *name);
void	print_error_msg(char *cmd, char *msg);
void	print_error(char **args, char *msg);
t_env	*find_env_node(t_data *data, char *env_var);
int		count_args(char **args);
void	execute(t_data *data, t_command *cmd);
int		run_bltin(t_data *data, t_command *cmd);
void	run_external(t_data *data, t_command *cmd);
int		handle_error_arg(t_data *data, char *arg, char *msg, int error_code);
int		execute_cmd(t_data *data, t_command *cmd, char *path);
int		check_file_access(char *path);
char	*process_binary(t_data *data, char *arg);
int		check_file_access(char *path);
int		redirect_stream(t_data *data, int old_fd, int new_fd);
int		handle_redirs(t_data *data, t_command *cmd);
int	    process_heredoc(t_data *data, t_files *cur_node);
int     run_pipes(t_data *data, t_command *cmd, int cmd_count);
pid_t	create_process(void);
void	process_cmd(t_data *data, t_command *cmd);
void	free_fds(int **fds, int i);
int     handle_parent_process(pid_t pid);
void	cleanup_process_data(t_data *data);
void	process_cmd(t_data *data, t_command *cmd);

void    set_prompt_signals(void);
void	set_heredoc_signals(void);
void    reset_signals_to_default(void);

#endif
