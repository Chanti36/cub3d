
#include "../cub.h"

static int find_wall(t_game *game, int angle)
{
	(void)game;
	angle = 0;

	return (0);
}

void render_raycast(t_game *game)
{
	(void)game;
	int	x;
	int angle;

	x = 0;
	while (x < WINDOW_WIDTH)
	{
		//CUANDO SE RESETEA EN 360 ESTO FALLA
		angle = lerp(game->player.a - 45, game->player.a + 45, x / WINDOW_WIDTH);
		find_wall(game, angle);
		//render wall
		x++;
	}
}

/*
2d check
throw a ray based on x coord of screen and player angle and pos
follow ray till it hits a wall || max dist
use hit dist to determine wall height
	check ray on intersections with tile borders to check if its inside a wall
angle FOV = 90

To rotate a vector, multiply it with the rotation matrix
[ cos(a) -sin(a) ]
[ sin(a)  cos(a) ]
*/
