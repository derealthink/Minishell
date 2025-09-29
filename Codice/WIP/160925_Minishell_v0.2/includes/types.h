/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aielo <aielo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 18:05:02 by aielo             #+#    #+#             */
/*   Updated: 2025/09/29 18:26:26 by aielo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPES_H
# define TYPES_H

# include <stdbool.h>
# include <signal.h>

# define true 1
# define false 0

extern volatile sig_atomic_t global_signal;

typedef	enum e_state
{
	STATE_NORMAL,
	STATE_SQUOTES,
	STATE_DQUOTES
}	t_state;

typedef enum	s_type
{
	TYPE_ARG,
	TYPE_RIN,
	TYPE_ROUT,
	TYPE_HERED,
	TYPE_APP,
	TYPE_PIPE
}	t_type;

typedef	struct s_token
{
	char	*value;
	struct	s_token	*next;
	t_type	type;
	int		moved;
}	t_token;

typedef	struct l_table
{
	t_token	*head;
	t_token	*tail;
}	t_table;

typedef struct	s_cmd
{
	char			*path;
	char			**args;
	char			*input_file;
	char			*output_file;
	char			*delimiter;
	bool			trunc_mode;  // 1 = truncate , 0 = append
	struct s_cmd	*next;
}	t_cmd;

#endif