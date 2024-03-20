
#include "cub.h"

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
	{
		if (game->collision)
			game->collision = 0;
		else
			game->collision = 1;
	}
	else if (keycode == 31)
		open_door(game);
	else if (keycode == 32)
	{
		if (game->eye)
			game->eye = 0;
		else
			game->eye = 20;
	}
	else if (keycode == KEY_ESCAPE)
		exit_game(game);
	return (0);
}
