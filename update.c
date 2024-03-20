
#include "cub.h"

int	close_win(t_game *game)
{
	exit_game(game);
	return (0);
}

static int	collision_check(t_game *game, float move_x, float move_y)
{
	int	space_x;
	int	space_y;

	if (move_x < 0)
		space_x = -10;
	else
		space_x = 10;
	if (move_y < 0)
		space_y = -10;
	else
		space_y = 10;
	if (game->map[(int)(game->player.y + move_y + space_y) / 64] \
		[(int)(game->player.x + move_x + space_x) / 64] == '1' || \
		game->map[(int)(game->player.y + move_y + space_y) / 64] \
		[(int)(game->player.x + move_x + space_x) / 64] == 'D')
	{
		if ((int)(game->player.y + move_y) % 64 == 0)
			game->player.y += move_y;
		else if ((int)(game->player.x + move_x) % 64 == 0)
			game->player.x += move_x;
		return (1);
	}
	return (0);
}

static void	movement(t_game *game)
{
	float	angle;
	float	move_x;
	float	move_y;

	angle = game->player.a + game->player.v_speed;
	if (angle > 360)
		angle -= 360;
	if (angle < 0)
		angle += 360;
	move_x = game->player.speed * cos(angle * M_PI / 180);
	move_y = game->player.speed * -sin(angle * M_PI / 180);
	if (game->collision && collision_check(game, move_x, move_y))
		return ;
	game->player.x += move_x;
	game->player.y += move_y;
	if (game->player.x < 0)
		game->player.x = 0.5;
	if (game->player.x > game->max_x * 64)
		game->player.x = game->max_x * 64 - 0.5;
	if (game->player.y < 0)
		game->player.y = 0.5;
	if (game->player.y > game->max_y * 64)
		game->player.y = game->max_y * 64;
}

int	update(t_game *game)
{
	movement(game);
	game->player.speed -= game->player.max_speed / game->player.speed;
	if (game->player.speed < 0)
		game->player.speed = 0;
	return (0);
}
