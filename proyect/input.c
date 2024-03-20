/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgil-moy <sgil-moy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 15:55:43 by sgil-moy          #+#    #+#             */
/*   Updated: 2024/03/20 16:53:43 by sgil-moy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

static void	open_door_aux(t_game *game)
{
	if (game->map[((int)game->player.y / 64) + 2] \
					[(int)game->player.x / 64] && \
		game->map[((int)game->player.y / 64) + 2] \
		[(int)game->player.x / 64] == 'D')
		game->map[((int)game->player.y / 64) + 2] \
		[(int)game->player.x / 64] = '0';
	else if (game->map[((int)game->player.y / 64) - 2] \
	[(int)game->player.x / 64] && \
			game->map[((int)game->player.y / 64) - 2] \
			[(int)game->player.x / 64] == 'D')
		game->map[((int)game->player.y / 64) - 2] \
		[(int)game->player.x / 64] = '0';
	else if (game->map[((int)game->player.y / 64)] \
	[((int)game->player.x / 64) + 2] && \
			game->map[((int)game->player.y / 64)] \
			[((int)game->player.x / 64) + 2] == 'D')
		game->map[((int)game->player.y / 64)] \
		[((int)game->player.x / 64) + 2] = '0';
	else if (game->map[((int)game->player.y / 64)] \
	[((int)game->player.x / 64) - 2] && \
			game->map[((int)game->player.y / 64)] \
			[((int)game->player.x / 64) - 2] == 'D')
		game->map[((int)game->player.y / 64)] \
		[((int)game->player.x / 64) - 2] = '0';
}

static void	open_door(t_game *game)
{
	if (game->map[((int)game->player.y / 64) + 1] \
					[(int)game->player.x / 64] && \
		game->map[((int)game->player.y / 64) + 1] \
		[(int)game->player.x / 64] == 'D')
		game->map[((int)game->player.y / 64) + 1] \
		[(int)game->player.x / 64] = '0';
	else if (game->map[((int)game->player.y / 64) - 1] \
	[(int)game->player.x / 64] && \
			game->map[((int)game->player.y / 64) - 1] \
			[(int)game->player.x / 64] == 'D')
		game->map[((int)game->player.y / 64) - 1] \
		[(int)game->player.x / 64] = '0';
	else if (game->map[((int)game->player.y / 64)] \
	[((int)game->player.x / 64) + 1] && \
			game->map[((int)game->player.y / 64)] \
			[((int)game->player.x / 64) + 1] == 'D')
		game->map[((int)game->player.y / 64)] \
		[((int)game->player.x / 64) + 1] = '0';
	else if (game->map[((int)game->player.y / 64)] \
	[((int)game->player.x / 64) - 1] && \
			game->map[((int)game->player.y / 64)] \
			[((int)game->player.x / 64) - 1] == 'D')
		game->map[((int)game->player.y / 64)] \
		[((int)game->player.x / 64) - 1] = '0';
	open_door_aux(game);
}

void	move(t_game *game, int dir)
{
	if (game->player.speed == 0)
		game->player.speed = 10;
	else
		game->player.speed += game->player.max_speed / game->player.speed - 1;
	if (game->player.speed > game->player.max_speed)
		game->player.speed = game->player.max_speed;
	if (dir == 0)
		game->player.v_speed = 0;
	if (dir == 1)
		game->player.v_speed = 90;
	if (dir == 2)
		game->player.v_speed = 180;
	if (dir == 3)
		game->player.v_speed = 270;
}

static void	key_hook_aux(int keycode, t_game *game)
{
	if (keycode == KEY_P)
	{
		if (game->collision)
			game->collision = 0;
		else
			game->collision = 1;
	}
	else if (keycode == KEY_O)
		open_door(game);
	else if (keycode == KEY_U)
	{
		if (game->eye)
			game->eye = 0;
		else
			game->eye = 20;
	}
	else if (keycode == KEY_ESCAPE)
		exit_game(game);
}

int	key_hook(int keycode, t_game *game)
{
	if (keycode == KEY_W || keycode == KEY_UP)
		move(game, 0);
	else if (keycode == KEY_A || keycode == KEY_LEFT)
		move(game, 1);
	else if (keycode == KEY_S || keycode == KEY_DOWN)
		move(game, 2);
	else if (keycode == KEY_D || keycode == KEY_RIGHT)
		move(game, 3);
	else
		key_hook_aux(keycode, game);
	return (0);
}
