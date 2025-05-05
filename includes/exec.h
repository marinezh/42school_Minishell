#ifndef EXEC_H
# define EXEC_H

void 	init_data(t_data *data, char **env);
int 	ft_pwd(t_data *data, t_command *cmd);
int		ft_echo(t_data *data, t_command *cmd);
int		ft_env(t_data *data, t_command *cmd);
int		ft_export(t_data *data, t_command *cmd);
void	free_envp_array(char **envp);
void	free_env_list(t_env *env);
int		run_bltin(t_data *data, t_command *cmd);
void	update_envp_array(t_data *data, t_env *envp_list);
void	node_add_last(t_env **envp_list, t_env *new_node);
t_env	*create_env_node(char *str);

// don't forget to delete
// this is just to print linked list
void	print_envp_list(t_env *envp_list);

#endif
