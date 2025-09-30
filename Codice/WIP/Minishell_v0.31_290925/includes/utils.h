/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aielo <aielo@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 15:44:44 by aielo             #+#    #+#             */
/*   Updated: 2025/09/30 16:36:58 by aielo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include <stdio.h>
# include <stdlib.h>
# include <signal.h>
# include <termios.h>
# include <readline/readline.h>
# include "types.h"
# include "libft.h"

void	print_logo(void);

void	set_signal_action(void);
void	set_terminal_mode(void);
void	signal_handler(int signum);
void	reset_signals_child(void);

void	token_list_clear(t_table *list);
void	cmd_list_clear(t_cmd *cmd_list);

#endif