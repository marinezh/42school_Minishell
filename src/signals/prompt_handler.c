#include "minishell.h"

volatile sig_atomic_t sig_received = 0;

static void	handler(int sig)
{
	if (sig == SIGINT)
	{
		sig_received = 1;
		write(1, "\n", 1);
		// rl_on_new_line(); //tells readline that cursor has moved to a new line
		// rl_replace_line("", 0); //clear the current input line
		// rl_redisplay(); //display a fresh prompt
	}
}

void	set_prompt_signals(void)
{
	struct sigaction sa_int;
	struct sigaction sa_quit;

	ft_memset(&sa_int, 0, sizeof(sa_int));
	sa_int.sa_handler = handler;
	sa_int.sa_flags = SA_RESTART; //sys calls restart automatically, code doesn't even know about interruption
	sigemptyset(&sa_int.sa_mask);
	sigaction(SIGINT, &sa_int, NULL);
	ft_memset(&sa_quit, 0, sizeof(sa_quit));
	sa_quit.sa_handler = SIG_IGN;
	sigemptyset(&sa_quit.sa_mask);
	sigaction(SIGQUIT, &sa_quit, NULL);
}

void    reset_signals_to_default(void)
{
    struct sigaction sa;

    ft_memset(&sa, 0, sizeof(sa));
    sa.sa_handler = SIG_DFL;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    sigaction(SIGINT, &sa, NULL);
    sigaction(SIGQUIT, &sa, NULL);
}
