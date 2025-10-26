/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminal_config.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aielo <aielo@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 17:35:44 by aielo             #+#    #+#             */
/*   Updated: 2025/10/26 22:22:02 by aielo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "configuration.h"

//static void	init_new_term(struct termios *new_term);

void	set_terminal_mode(t_minishell *shell)
{
	if (tcgetattr(STDIN_FILENO, &shell->original_termios) == -1)
	{
		shell->last_exit_status = 9;
		return ;
	}
	shell->new_termios = shell->original_termios;
//	init_new_term(&shell->new_termios);
	if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &shell->new_termios) == -1)
		return ;
}

void	restore_terminal(t_minishell *shell)
{
	if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &shell->original_termios) == -1)
	{
		shell->last_exit_status = 9;
		return ;
	}
}

/*
static void init_new_term(struct termios *new_term)
{
//	new_term->c_lflag &= ~(ECHO);
//	new_term->c_lflag &= ~(ECHOCTL);
//	new_term->c_lflag &= ~(IEXTEN);
//	new_term->c_lflag &= ~(ICANON);
//	new_term->c_iflag &= ~(BRKINT | ICRNL | INPCK | ISTRIP | IXON);
//	new_term->c_lflag &= ~(ISIG);
//	new_term->c_cc[VMIN] = 1;
//	new_term->c_cc[VTIME] = 0;
}
*/