/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_heredoc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aielo <aielo@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/26 22:18:50 by aielo             #+#    #+#             */
/*   Updated: 2025/10/26 22:22:40 by aielo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "configuration.h"

void	setup_heredoc_signals(void)
{
	struct sigaction	sa;

	sa.sa_handler = here_doc_sigint_handler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGINT, &sa, NULL);
	sa.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &sa, NULL);
}

void	here_doc_sigint_handler(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	g_global_signal = 1;
	exit(130);
}
