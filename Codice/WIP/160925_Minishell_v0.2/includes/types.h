/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aielo <aielo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 18:05:02 by aielo             #+#    #+#             */
/*   Updated: 2025/09/25 18:42:21 by aielo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPES_H
# define TYPES_H

# include <stdbool.h>
<<<<<<< HEAD
=======
#define true 1
#define false 0
>>>>>>> 821996f5956f2940a42a57deaa41275e697cc7e7

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