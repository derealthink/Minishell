/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aielo <aielo@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 17:35:44 by aielo             #+#    #+#             */
/*   Updated: 2025/09/30 16:47:10 by aielo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

volatile sig_atomic_t global_signal = 0;

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