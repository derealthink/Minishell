/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aielo <aielo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 13:33:49 by aielo             #+#    #+#             */
/*   Updated: 2025/09/25 15:51:43 by aielo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main()
{
	char	*line;
	t_table	*token_list;

	print_logo();
	while (1)
	{
		line = readline("minishell> ");
		if (!line)
		{
			free (line);
			break ;
		}
		token_list = lexer(line);
		print_tokens(token_list);
		free(line);
// free della linked list token_list?
	}
	return (0);
}
