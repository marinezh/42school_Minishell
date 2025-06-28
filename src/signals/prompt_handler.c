#include "minishell.h"
#include <readline/readline.h>
#include <readline/history.h>

// declared JUST for MacOS
extern void rl_replace_line(const char *text, int clear_undo);

static struct termios original_term;
static int term_stored = 0;
volatile sig_atomic_t sig_received = 0;

// Initialize the terminal settings - call this at the start of your program
void initialize_terminal_settings(void)
{
    if (isatty(STDIN_FILENO)) {
        tcgetattr(STDIN_FILENO, &original_term);
        term_stored = 1;
    }
}

// Check if we're in a child process
static int is_in_child_process(void)
{
    struct termios current_term;
    
    if (!term_stored || !isatty(STDIN_FILENO))
        return 0;
        
    // Get current terminal settings
    if (tcgetattr(STDIN_FILENO, &current_term) != 0)
        return 0;
        
    // Compare with original settings
    return (ft_memcmp(&current_term, &original_term, sizeof(struct termios)) != 0);
}


static void	handler(int sig)
{
	if (sig == SIGINT)
	{
		sig_received = 1;
		if (!is_in_child_process())
		{
			write(1, "\n", 1);
			rl_on_new_line(); //tells readline that cursor has moved to a new line
			rl_replace_line("", 0); //clear the current input line
			rl_redisplay(); //display a fresh prompt
		}
		rl_done = 1;
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
