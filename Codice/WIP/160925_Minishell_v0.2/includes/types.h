/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aielo <aielo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 18:05:02 by aielo             #+#    #+#             */
/*   Updated: 2025/09/25 15:41:04 by aielo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPES_H
# define TYPES_H

# include <stdbool.h>
#define true 1
#define false 0

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

typedef enum	s_type
{
	TYPE_ARG,
	TYPE_RIN,
	TYPE_ROUT,
	TYPE_HERED,
	TYPE_APP,
	TYPE_PIPE
}	t_type;

#endif