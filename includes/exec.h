#ifndef EXEC_H
# define EXEC_H

typedef struct s_llist t_llist;
typedef struct s_edata t_edata;
typedef int (*t_bltin) (t_llist *, t_edata);

struct s_llist
{
    char    *key;
    char    *value;
    struct t_llist *next;
};

struct s_edata
{
    char        *cmd_names[7];
    t_bltin     builtins[7];
    // char        **envp;
    // t_list      envp_list;
    // char        envp_f;
    // char        exit_t;
    // int         status;
};

void init_data(t_edata *edata);
int ft_pwd(t_llist *list, t_edata edata);

#endif
