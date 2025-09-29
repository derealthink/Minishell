/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aielo <aielo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 15:44:44 by aielo             #+#    #+#             */
/*   Updated: 2025/09/29 18:33:29 by aielo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include <stdio.h>
# include <stdlib.h>
# include <signal.h>
# include "types.h"
# include "libft.h"

void	print_logo(void);

void	set_signal_action(void);
void	signal_handler(int signum);

void	token_list_clear(t_table *list);

#endif