/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aielo <aielo@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 18:05:02 by aielo             #+#    #+#             */
/*   Updated: 2025/10/14 14:22:20 by aielo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPES_H
# define TYPES_H

# include <stdbool.h>
# include <signal.h>

# define true 1
# define false 0

extern volatile sig_atomic_t	g_global_signal;

typedef struct s_generic_list
{
	struct s_generic_list	*next;
}	t_generic_list;

typedef enum e_state
{
	STATE_NORMAL,
	STATE_SQUOTES,
	STATE_DQUOTES
}	t_state;

typedef enum s_type
{
	TYPE_ARG,
	TYPE_RIN,
	TYPE_ROUT,
	TYPE_HERED,
	TYPE_APP,
	TYPE_ENV,
	TYPE_PIPE
}	t_type;

typedef struct s_token
{
	struct s_token	*next;
	char			*value;
	t_type			type;
	int				moved;
}	t_token;

typedef struct l_table
{
	t_token	*head;
	t_token	*tail;
}	t_table;

typedef struct s_cmd
{
	struct s_cmd	*next;
	char			*path;
	char			**args;
	char			*input_file;
	char			*output_file;
	char			*delimiter;
	int				trunc_mode;
}	t_cmd;

typedef struct s_new_envp
{
	struct s_new_envp	*next;
	char				*name;
	char				*value;
}	t_new_envp;

typedef struct s_env_list
{
	t_new_envp	*head;
	int			len_envp;
}	t_env_list;

typedef struct s_minishell
{
	t_env_list	*env_list;
	t_table		*token_list;
	t_cmd		*cmd_list;
	int			last_exit_status;
	bool		is_interactive;
}	t_minishell;

#endif