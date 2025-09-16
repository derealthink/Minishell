/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aielo <aielo@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 15:44:14 by aielo             #+#    #+#             */
/*   Updated: 2025/09/16 13:25:50 by aielo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "libft.h"
# include "types.h"

int	is_builtin(char *cmd);
int	execute_builtin(t_cmd *cmd, char ***envp);

int ft_echo(char **args);

#endif