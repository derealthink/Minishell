/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   configuration.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aielo <aielo@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 15:44:44 by aielo             #+#    #+#             */
/*   Updated: 2025/10/21 18:00:56 by aielo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONFIGURATION_H
# define CONFIGURATION_H

# include <stdio.h>
# include <stdlib.h>
# include <signal.h>
# include <termios.h>
# include <readline/readline.h>
# include "types.h"
# include "libft.h"
# include "utils.h"

void	set_terminal_mode(t_minishell *shell);
void	restore_terminal(t_minishell *shell);

int		shell_is_interactive(void);

void	handle_sigint(int sig);
void	set_signal_handler(int signum, void (*handler)(int), int flags);
void	setup_interactive_parent_signals(void);
void	setup_child_signals(void);

void	setup_heredoc_signals(void);
void	here_doc_sigint_handler(int sig);

#endif