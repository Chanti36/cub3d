
#include "../cub.h"

static int	find_wall(t_game *game, float angle)
{
	t_vec2	look_vec;
	int		i;
	int		j;
	int look_dir;
	// 123
	// 4 5
	// 678

	//sacar el vector hacia donde miras
	look_vec = find_vector(game, angle);
	//hay que iterar por coseno y seno
	while (i < game->max_x && j < game->max_y && i > 0 && j > 0)
	{
		i += look_vec.x;
	}
	//saber para que cuadrante miras

	//avanzar en donde pille mas rapido hasta colisionar

	//checkear colision


	return (0);
}

void	render_raycast(t_game *game)
{
	int	x;
	int	angle;

	x = 0;
	while (x < WINDOW_WIDTH)
	{
		angle = lerp(game->player.a + 45, \
		game->player.a - 45, x / WINDOW_WIDTH);
		if (angle < 0)
			angle += 360;
		else if (angle >= 360)
			angle -= 360;
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
