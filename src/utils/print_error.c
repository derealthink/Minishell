/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aielo <aielo@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 13:37:50 by aielo             #+#    #+#             */
/*   Updated: 2025/10/07 16:29:20 by aielo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void	print_simple_error(char *cmd, char *text)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(text, 2);
	ft_putstr_fd("\n", 2);
}

void	print_quoted_error(char *cmd, char *arg, char *text)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": '", 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd("': ", 2);
	ft_putstr_fd(text, 2);
	ft_putstr_fd("\n", 2);
}

void	print_unquoted_error(char *cmd, char *arg, char *text)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(text, 2);
	ft_putstr_fd("\n", 2);
}

void	print_quoted_exe_error(char *cmd, char *arg, char *text)
{
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": '", 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd("': ", 2);
	ft_putstr_fd(text, 2);
	ft_putstr_fd("\n", 2);
}

void	print_unquoted_exe_error(char *cmd, char *text)
{
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(text, 2);
	ft_putstr_fd("\n", 2);
}
