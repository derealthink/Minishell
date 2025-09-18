/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aielo <aielo@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 13:33:49 by aielo             #+#    #+#             */
/*   Updated: 2025/09/16 17:03:11 by aielo            ###   ########.fr       */
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
	}
	return (0);
}
