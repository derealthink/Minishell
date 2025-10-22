/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aielo <aielo@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 17:35:44 by aielo             #+#    #+#             */
/*   Updated: 2025/10/22 08:49:00 by aielo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "configuration.h"

volatile sig_atomic_t g_global_signal = 0;

int	shell_is_interactive(void)
{
	if (isatty(STDIN_FILENO))
		return (1);
	else
		return (0);
}

void	setup_interactive_parent_signals(void)
{
	set_signal_handler(SIGINT, handle_sigint, 0);
	set_signal_handler(SIGQUIT, SIG_IGN, 0);
}

void	setup_child_signals(void)
{
	set_signal_handler(SIGINT, SIG_DFL, 0);
	set_signal_handler(SIGQUIT, SIG_IGN, 0);
//	set_signal_handler(SIGQUIT, SIG_DFL, 0);
}

void	set_signal_handler(int signum, void (*handler)(int), int flags) //passo shell per settare exit_status = -1 in caso fallisca sigaction?
{
	struct sigaction sa;

	sa.sa_flags = flags;
	sa.sa_handler = handler;
	sigemptyset(&sa.sa_mask);
	if (sigaction(signum, &sa, NULL) == -1)
		print_simple_error("sigaction error", "Invalid argument");
}

void	handle_sigint(int sig)
{
	g_global_signal = sig;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	here_doc_sigint_handler(int sig)
{
    (void)sig;
	g_global_signal = SIGINT;
	write(STDOUT_FILENO, "\n", 1);
    // Just close and exit - let parent handle the cleanup
    //close(STDIN_FILENO);
    //exit(130); // Exit heredoc child process on SIGINT
}

void	setup_heredoc_signals(void)
{
    struct sigaction sa;

    sa.sa_handler = here_doc_sigint_handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
}

/*
#include "minishell.h"

* signal_reset_prompt:
*	Resets the readline user input prompt for interactive signal handling.
*
void	signal_reset_prompt(int signo)
{
	(void)signo;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

* set_signals_interactive:
*	Sets the behavior in response to SIGINT (ctrl-c) and SIGQUIT (ctrl-\).
*	SIGINT resets the user input prompt to a new blank line.
*	SIGQUIT is ignored.
*	Used when minishell is in interactive mode, meaning it is awaiting
*	user input.
*
void	set_signals_interactive(void)
{
	struct sigaction	act;

	ignore_sigquit();
	ft_memset(&act, 0, sizeof(act));
	act.sa_handler = &signal_reset_prompt;
	sigaction(SIGINT, &act, NULL);
}

* signal_print_newline:
*	Prints a newline for noninteractive signal handling.
*
void	signal_print_newline(int signal)
{
	(void)signal;
	rl_on_new_line();
}

* set_signals_noninteractive:
*	Sets the behavior in response to SIGINT (ctrl -c) and SIGQUIT (ctrl -\).
*	Used when minishell is in noninteractive mode, meaning it is not awaiting
*	user input. For example, when a command is running (i.e. cat), minishell
*	should not react to SIGINT and SIGQUIT because only the running process (cat)
*	needs to react to those signals.
*
void	set_signals_noninteractive(void)
{
	struct sigaction	act;

	ft_memset(&act, 0, sizeof(act));
	act.sa_handler = &signal_print_newline;
	sigaction(SIGINT, &act, NULL);
	sigaction(SIGQUIT, &act, NULL);
}

* ignore_sigquit:
*	Replaces SIGQUIT signals (ctrl-\) with SIG_IGN to ignore
*	the signal.
*
void	ignore_sigquit(void)
{
	struct sigaction	act;

	ft_memset(&act, 0, sizeof(act));
	act.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &act, NULL);
}
*/

/*
 my_termios.c_lflag &= ~(ICANON | ECHO | ECHOE | ECHOK | ECHONL | ECHOCTL | ECHOPRT | ECHOKE);
        my_termios.c_oflag &= ~OPOST; // Raw output is selected by resetting the OPOST option in the c_oflag member: 
        my_termios.c_cc[VINTR]    = 0;     // Ctrl-c 
        my_termios.c_cc[VQUIT]    = 0;     // Ctrl-\ 
        my_termios.c_cc[VERASE]   = 0;     // del 
        my_termios.c_cc[VKILL]    = 0;     // @ 
        my_termios.c_cc[VEOF]     = 0;     // Ctrl-d 
        my_termios.c_cc[VTIME]    = 0;     // inter-character timer unused 
        my_termios.c_cc[VMIN]     = 1;     // blocking read until 1 character arrives 
        my_termios.c_cc[VSWTC]    = 0;     // '\0' 
        my_termios.c_cc[VSTART]   = 0;     // Ctrl-q  
        my_termios.c_cc[VSTOP]    = 0;     // Ctrl-s 
        my_termios.c_cc[VSUSP]    = 0;     // Ctrl-z 
        my_termios.c_cc[VEOL]     = 0;     // '\0' 
        my_termios.c_cc[VREPRINT] = 0;     // Ctrl-r 
        my_termios.c_cc[VDISCARD] = 0;     // Ctrl-u 
        my_termios.c_cc[VWERASE]  = 0;     // Ctrl-w 
        my_termios.c_cc[VLNEXT]   = 0;     // Ctrl-v 
        my_termios.c_cc[VEOL2]    = 0;     // '\0'

*/