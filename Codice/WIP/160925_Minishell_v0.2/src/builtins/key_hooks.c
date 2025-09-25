/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aielo <aielo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 18:05:58 by aielo             #+#    #+#             */
/*   Updated: 2025/09/24 18:06:34 by aielo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
# include "X11/keysym.h"

mlx_key_hook(game->win_ptr, key_hook, game);

int	key_hook(int keycode, void *param)
{
	t_map	*game;

	game = (t_map *)param;
	if (keycode == XK_Escape)
	{
		game_cleanup(game);
		exit (0);
	}
	if (keycode == XK_Up)
		player_movements_up(game);
	if (keycode == XK_Down)
		player_movements_down(game);
	if (keycode == XK_Left)
		player_movements_left(game);
	if (keycode == XK_Right)
		player_movements_right(game);
	coin_mechanic(game);
	exit_mechanic(game);
	return (0);
}

*/