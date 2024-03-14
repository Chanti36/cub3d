
#include "cub.h"

static void	movement(t_game *game)
{
	float angle;

	angle = game->player.a + game->player.v_speed;
	if (angle > 360)
		angle -=360;
	if (angle < 0)
		angle += 360;
	game->player.x += game->player.speed * cos(angle * M_PI / 180);
	game->player.y += game->player.speed * -sin(angle * M_PI / 180);
	if (game->player.x < 0)
		game->player.x = 32;
	if (game->player.x > game->max_x * 64)
		game->player.x = game->max_x * 64 - 32;

	if (game->player.y < 0)
		game->player.y = 32;
	if (game->player.y > game->max_y * 64)
		game->player.y = game->max_y * 64;
}
int	update(t_game *game)
{
	movement(game);
	game->player.speed = 0;
	return(0);
}