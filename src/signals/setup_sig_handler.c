#include "minishell.h"

void    handler(int sig)
{
    if (sig == SIGINT)
        sig_received = 1;
    else if (sig == SIGQUIT)
        sig_received = 2;
}

void    setup_sig_handler(void)
{
    struct sigaction sa;

    ft_memset(&sa, 0, sizeof(sa));
    sa.sa_handler = handler;
    sa.sa_flags = 0;
    sigemptyset(&sa.sa_mask);
    sigaction(SIGINT, &sa, NULL);
    sigaction(SIGQUIT, &sa, NULL);
}