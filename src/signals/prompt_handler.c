#include "minishell.h"
#include <readline/readline.h>
#include <readline/history.h>

// declared JUST for MacOS
extern void rl_replace_line(const char *text, int clear_undo);

volatile sig_atomic_t g_sig_received = 0;

static void	handler(int sig)
{
	//if (sig == SIGINT)
	//{
		g_sig_received = sig;
		// write(1, "\n", 1);
		// rl_on_new_line(); //tells readline that cursor has moved to a new line
		// rl_replace_line("", 0); //clear the current input line
		// rl_redisplay(); //display a fresh prompt
		// rl_done = 1;
		// g_sig_received = 0;
	//}
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

int	rl_signal_handler(void)
{
	if (g_sig_received == SIGINT)
	{
		// ft_putzendl("^C");
		rl_on_new_line();
		rl_replace_line("", 1);
		rl_redisplay();
		g_sig_received = 0;
	}
	return (EXIT_SUCCESS);
}