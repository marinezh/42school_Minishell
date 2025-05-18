#include "minishell.h"

void	handle_permissoin_denied(t_data * data, char *arg)
{
	data->status = ERROR_ISDIR;
    ft_putstr_fd("minishell: ", STDERR_FILENO);
    ft_putstr_fd(arg, STDERR_FILENO);
    ft_putstr_fd(": Permission denied\n", STDERR_FILENO);
}

char    *parse_path_env(t_data *data, char *arg)
{
    t_env   *path_ptr = NULL;
    char    **path_dirs = NULL;
    char    *tmp;
    char    *res;
    int     i;

    path_ptr = find_env_name(data, "PATH");
    if (path_ptr)
        path_dirs = ft_split(path_ptr->value, ':');
    i = 0;
    if (path_dirs)
    {
        while (path_dirs[i])
        {
            tmp = path_dirs[i];
            path_dirs[i] = ft_strjoin(tmp, "/");
            free(tmp);
            tmp = path_dirs[i];
            path_dirs[i] = ft_strjoin(tmp, arg);
            free(tmp);
            if (access(path_dirs[i], F_OK | X_OK) == 0)
            {
                res = ft_strdup(path_dirs[i]);
                free_double_array(path_dirs);
                return(res);
            }
            if (access(path_dirs[i], F_OK) == 0 && 
                access(path_dirs[i], X_OK) != 0)
            {
                handle_permissoin_denied(data, arg);
                free_double_array(path_dirs);
                return(NULL);
            }
            i++;
        }
    }
    free_double_array(path_dirs);
    return (NULL);
}

void	handle_no_command_found(t_data * data, char *arg)
{
	data->status = ERROR_CMD_NOT_FOUND;
    ft_putstr_fd("minishell: ", STDERR_FILENO);
    ft_putstr_fd(arg, STDERR_FILENO);
    ft_putstr_fd(": command not found\n", STDERR_FILENO);
}



int execute_cmd(t_data *data, t_command *cmd, char *path)
{
    pid_t   pid;
    int     wstatus;
    int     exit_code;

    exit_code = 0;
    pid = fork();
    if (pid == -1)
    {
        perror("fork");
        return (-1);
    }
    if (pid == 0)
    {
        if (execve(path, cmd->args, data->envp) == -1)
        {
            perror("execve");
            if (errno == ENOENT)
                exit(ERROR_CMD_NOT_FOUND);
            else if (errno == EACCES)
                exit(ERROR_ISDIR);
            else   
                exit(ERROR_GENERIC);
        }
    }
    else
    {
        waitpid(pid, &wstatus, 0);
        if (WIFEXITED(wstatus))
            exit_code = WEXITSTATUS(wstatus);
        // else if (WIFSIGNALED(wstatus))  // Add this to properly handle signals
        // {
        //     exit_code = 128 + WTERMSIG(wstatus);
            
        //     // Print message for certain signals
        //     if (WTERMSIG(wstatus) == SIGINT)
        //         ft_putstr_fd("\n", STDERR_FILENO);
        //     else if (WTERMSIG(wstatus) == SIGQUIT)
        //         ft_putstr_fd("Quit (core dumped)\n", STDERR_FILENO);
        // }
        else
            exit_code = ERROR_GENERIC;
    }
    return(exit_code);
}

int     run_external(t_data *data, t_command *cmd)
{
    char    *path;
    char    *path_to_free;
    int     exit_status;

    path_to_free = NULL;
    if (access(cmd->args[0], F_OK | X_OK) == 0)
        path = cmd->args[0];
    else if (access(cmd->args[0], F_OK) == 0 &&
        access(cmd->args[0], X_OK) != 0)
    {
        handle_permissoin_denied(data, cmd->args[0]);
        return (-1);
    }
    else
    {
        path = parse_path_env(data, cmd->args[0]);
        path_to_free = path;
        if (!path)
        {
            handle_no_command_found(data, cmd->args[0]);
            return (-1);
        }
    }
    exit_status = execute_cmd(data, cmd, path);
    data->status = exit_status;
    if (path_to_free)
        free(path_to_free);
    return (exit_status);
}


// bash command - test -x filename.c
//cat: test.txt: Permission denied - 1
//cat: adfas: No such file or directory - 1
//asdlfkja bash: kjsahfhsdf: command not found - 127

//1) not exist
//2) exist not executable
//3) exist and executable