/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aielo <aielo@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 17:35:44 by aielo             #+#    #+#             */
/*   Updated: 2025/10/26 22:23:09 by aielo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "configuration.h"

volatile sig_atomic_t	g_global_signal = 0;

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
}

void	set_signal_handler(int signum, void (*handler)(int), int flags)
{
	struct sigaction	sa;

	sa.sa_flags = flags;
	sa.sa_handler = handler;
	sigemptyset(&sa.sa_mask);
	if (sigaction(signum, &sa, NULL) == -1)
		print_simple_error("sigaction error", "Invalid argument");
}

void	handle_sigint(int sig)
{
	(void)sig;
	g_global_signal = SIGINT;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}
