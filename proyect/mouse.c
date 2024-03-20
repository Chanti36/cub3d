/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgil-moy <sgil-moy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 16:37:10 by sgil-moy          #+#    #+#             */
/*   Updated: 2024/03/20 16:38:55 by sgil-moy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

static void	move_cam(t_game *game, float spd)
{
	game->player.a += spd;
	if (game->player.a < 0)
		game->player.a += 360;
	else if (game->player.a >= 360)
		game->player.a -= 360;
}

int	mouse_hook(int x, int y, t_game *game)
{
	(void) y;
	if (x < WINDOW_WIDTH / 2)
		move_cam(game, -lerp(0, 200, \
		(float)(x - WINDOW_WIDTH / 2) / (float)WINDOW_WIDTH));
	else
		move_cam(game, lerp(0, 200, \
		-(float)(x - WINDOW_WIDTH / 2) / (float)WINDOW_WIDTH));
	mlx_mouse_move(game->win, WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
	return (0);
}
