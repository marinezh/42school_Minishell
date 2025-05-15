#include "minishell.h"

char    *parse_path_env(t_data *data, char *cmd)
{
    t_env *path_ptr = NULL;
    char **path_dirs = NULL;
    int i;
    (void)cmd;

    path_ptr = find_env_name(data, "PATH");
    if (path_ptr)
        path_dirs = ft_split(path_ptr->value, ':');
    i = 0;
    if (path_dirs)
    {
        while (path_dirs[i])
        {
            printf("%s\n", path_dirs[i]);
            i++;
        }
    }

    return (NULL);
}

int     run_external(t_data *data, t_command *cmd)
{
    // char    *path;

    // path = 
    parse_path_env(data, cmd->args[0]);
    return (0);
}


//find out what is it
// char *path = find_exec_path(cmd->args[0], data->envp);
// if (!path)
// {
// 	fprintf(stderr, "%s: command not found\n", cmd->args[0]);
// 	data->status = 127;
// 	return 127;
// }

// // Run the executable
// execve(path, cmd->args, data->envp);
// perror("execve"); // Only reached if execve fails
// free(path);
// data->status = 126;
// return 126;