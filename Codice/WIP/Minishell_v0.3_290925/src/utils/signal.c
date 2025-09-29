/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aielo <aielo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 17:35:44 by aielo             #+#    #+#             */
/*   Updated: 2025/09/29 18:33:31 by aielo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

volatile sig_atomic_t global_signal = 0;

void	set_signal_action(void)
{
	struct sigaction sa;

	ft_bzero(&sa, sizeof(sa));
	if (global_signal == 3)
		sa.sa_handler = SIG_IGN;
	else
		sa.sa_handler = signal_handler;
	sa.sa_flags = 0;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGINT, &sa, NULL);
}

void	signal_handler(int signum)
{
	if (signum == SIGINT)
		global_signal = signum;
}
