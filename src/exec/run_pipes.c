#include"minishell.h"

void    close_unused_heredoc_fds(t_command *cmd, t_command *cur_cmd)
{
    t_command *iter_cmd;
    t_files *cur_in;

    iter_cmd = cmd;
    while (iter_cmd)
    {
        if (iter_cmd != cur_cmd)
        {
            cur_in = iter_cmd->in;
            while (cur_in)
            {
                if (cur_in->type == HEREDOC && cur_in->fd >= 0)
                    close(cur_in->fd);
                cur_in = cur_in->next;
            }
        }
        iter_cmd = iter_cmd->next;
    }
}


int run_pipes(t_data *data, t_command *cmd, int cmd_count)
{
    //created pids for processes == cmd_count
    pid_t   *pids;
    int     **fds;
    int     i;
    int     j;
    int     exit_code;
    t_command *cur_cmd;

    pids = calloc(cmd_count, sizeof(pid_t));
    if (!pids)
    {
        perror("calloc");
        return(-1);
    }

    //create array for fds{0,1}, number of pipes
    fds = calloc(cmd_count - 1, sizeof(int*));
    if(!fds)
    {
        free(pids);
        return(-1);
    }
    i = 0;
    while (i < cmd_count - 1)
    {
        fds[i] = calloc(2, sizeof(int));
        if (!fds[i])
        {
            perror("calloc");
            free_fds(fds, i);
            free(pids);
            return (-1);
        }
        i++;
    }
    i = 0;
    //create pipes and connect with fds
    while (i < (cmd_count - 1))
    {
        if (pipe(fds[i]) == -1)
        {
            perror("pipe");
            free_fds(fds, i);
            free(pids);
            return (-1);
        }
        i++;
    }

    i = 0;
    //create processes
    cur_cmd = cmd;
    while (i < cmd_count)
    {
        pids[i] = create_process();
        if (pids[i] == 0)
        {
            reset_signals_to_default();

            close_unused_heredoc_fds(cmd, cur_cmd);
            //redirect out/in
            if (i != cmd_count - 1)
                dup2(fds[i][1], STDOUT_FILENO);
            if (i != 0)
                dup2(fds[i - 1][0], STDIN_FILENO);
            j = 0;
            while (j < cmd_count - 1)
            {
                close(fds[j][0]);
                close(fds[j][1]);
                j++;
            }
            process_cmd(data, cur_cmd);
            exit(0);
        }
        cur_cmd = cur_cmd->next;
        i++;
    }
    i = 0;
    while (i < cmd_count - 1)
    {
        close(fds[i][0]);
        close(fds[i][1]);
        i++;
    }
    i = 0;
    while (i < cmd_count)
    {
        exit_code = handle_parent_process(pids[i]);

        data->status = exit_code;
        i++;
    }
    free(pids);
    free_fds(fds, cmd_count - 2);
    return(0);
}

//each process has its own fd table which is a copy of parent fd table
//fd in those tables reference the same objects for read end and write end