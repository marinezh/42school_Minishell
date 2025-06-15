#include "minishell.h"

static void	handler(int sig)
{
	if (sig == SIGINT)
	{
		sig_received = 1;
		write(1, "\n", 1);
		//rl_on_new_line(); //tells readline that cursor has moved to a new line
		//rl_replace_line("", 0); //clear the current input line
		//rl_redisplay(); //display a fresh prompt
	}
}

void	set_heredoc_signals(void)
{
	struct sigaction sa_int;
	struct sigaction sa_quit;

	ft_memset(&sa_int, 0, sizeof(sa_int));
	sa_int.sa_handler = handler;
	sa_int.sa_flags = 0;
	sigemptyset(&sa_int.sa_mask);
	sigaction(SIGINT, &sa_int, NULL);
	ft_memset(&sa_quit, 0, sizeof(sa_quit));
	sa_quit.sa_handler = SIG_IGN;
	sigemptyset(&sa_quit.sa_mask);
	sigaction(SIGQUIT, &sa_quit, NULL);
}