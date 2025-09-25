/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aielo <aielo@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 18:05:02 by aielo             #+#    #+#             */
/*   Updated: 2025/09/15 18:10:07 by aielo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPES_H
# define TYPES_H

typedef struct	s_cmd
{
	char			*path;
	char			**args;
	char			*input_file;
	char			*output_file;
	int				input_fd;
	int				output_fd;
	struct s_cmd	*next;
} t_cmd;

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