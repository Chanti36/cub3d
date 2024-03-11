
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
	(void)game;

	game->player.speed += 50;
	if (dir == 0)
		game->player.v_speed = 90;
	if (dir == 1)
		game->player.v_speed = 180;
	if (dir == 2)
		game->player.v_speed = 270;
	if (dir == 3)
		game->player.v_speed = 0;
}

static void	move_cam(t_game *game, float spd)
{
	game->player.a += spd;
	if (game->player.a < 0)
		game->player.a += 360;
	else if (game->player.a >= 360)
		game->player.a -= 360;
	printf("ANGULO: %f, VELOCIDAD: %f\n", game->player.a, spd);
}

int	mouse_hook(int x, int y, t_game *game)
{
	if (x < 0 || x > WINDOW_WIDTH || y < 0 || y > WINDOW_HEIGHT)
		return (0);
	if (!game->player.mouse_x && !game->player.mouse_y)
	{
		game->player.mouse_x = x;
		game->player.mouse_y = y;
		return (0);
	}
	if (x < game->player.mouse_x)
		move_cam(game, lerp(0, 10, \
		(float)(x - game->player.mouse_x) / (float)WINDOW_WIDTH));
	else
		move_cam(game, -lerp(0, 10, \
		-(float)(x - game->player.mouse_x) / (float)WINDOW_WIDTH));
	game->player.mouse_x = x;
	game->player.mouse_y = y;
	return (0);
}

int	key_hook(int keycode, t_game *game)
{
	printf("%d\n", keycode);
	if (keycode == KEY_W || keycode == KEY_UP)
		move(game, 0);
	if (keycode == KEY_A || keycode == KEY_LEFT)
		move(game, 1);
	if (keycode == KEY_S || keycode == KEY_DOWN)
		move(game, 2);
	if (keycode == KEY_D || keycode == KEY_RIGHT)
		move(game, 3);
	if (keycode == KEY_ESCAPE)
		exit_game(game);
	return (0);
}

int	close_win(t_game *game)
{
	exit_game(game);
	return (0);
}
