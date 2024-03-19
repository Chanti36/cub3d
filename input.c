
#include "cub.h"

//int	can_move(t_game *game, int dir)
//{
//	int	x;
//	int	y;

//	x = game->player.x;
//	y = game->player.y;
//	if (dir == 0)
//		y -= 1;
//	if (dir == 1)
//	{
//		game->player.dir = -1;
//		x -= 1;
//	}
//	if (dir == 2)
//		y += 1;
//	if (dir == 3)
//	{
//		game->player.dir = 1;
//		x += 1;
//	}
//	if (game->map.map[y][x] == '1' ||
//		//game->map.map[y][x] == '!' ||
//		(game->map.map[y][x] == 'E' &&
//		game->map.can_exit != 1))
//		return (-1);
//	return (0);
//}

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
	{
		game->player.v_speed = 90;
		//game->player.speed -= 2.5;
	}
	if (dir == 2)
		game->player.v_speed = 180;
	if (dir == 3)
	{
		game->player.v_speed = 270;
		//game->player.speed -= 2.5;
	}
}

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
	else if (keycode == 35)
		game->collision = 1;
	else if (keycode == KEY_ESCAPE)
		exit_game(game);
	return (0);
}

int	close_win(t_game *game)
{
	exit_game(game);
	return (0);
}
