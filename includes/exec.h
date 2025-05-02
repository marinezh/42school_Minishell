#ifndef EXEC_H
# define EXEC_H

void 	init_data(t_data *data, char **env);
int 	ft_pwd(t_data *data);
void	free_envp_array(char **envp);
void	free_env_list(t_env *env);
int		run_bltin(char **args, t_data *data);

// don't forget to delete
// this is just to print linked list
void	print_envp_list(t_env *envp_list);

#endif
