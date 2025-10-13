/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aielo <aielo@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 17:35:44 by aielo             #+#    #+#             */
/*   Updated: 2025/10/13 14:10:07 by aielo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "signals.h"

volatile sig_atomic_t g_global_signal = 0;

// alla fine del file ci sono note su quale env uploadare allo start di shell

void	set_signal_action(void)
{
	struct sigaction sa;

	ft_bzero(&sa, sizeof(sa));
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
	sa.sa_handler = signal_handler;
	sigaction(SIGINT, &sa, NULL);
	sa.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &sa, NULL);
}

void	set_terminal_mode(void)
{
	struct termios	term;

	if(tcgetattr(STDIN_FILENO, &term) == -1)
		return ;
//	term.c_cc[VQUIT] = _POSIX_VDISABLE;
//	term.c_cc[VSUSP] = _POSIX_VDISABLE;
//	term.c_cc[VSTOP] = _POSIX_VDISABLE;
//	term.c_cc[VSTART] = _POSIX_VDISABLE;
	term.c_lflag &= ~ECHOCTL;
	if (tcsetattr(STDIN_FILENO, TCSANOW, &term) == -1)
		return ;
}

void	signal_handler(int signum)
{
	if (signum == SIGINT)
		global_signal = signum;
}

void	reset_signals_child(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
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

/* UPDATE shell level in main

Place this function at the start of your minishell main function, after parsing the inherited environment.

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void update_shlvl(char **envp) {
    char *shlvl_str = getenv("SHLVL");
    int shlvl = shlvl_str ? atoi(shlvl_str) : 0;
    shlvl += 1;
    char new_shlvl[32];
    snprintf(new_shlvl, sizeof(new_shlvl), "%d", shlvl);
    setenv("SHLVL", new_shlvl, 1);  // Updates SHLVL in the shell's environment
}

*/
/**
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