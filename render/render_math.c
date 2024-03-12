
#include "../cub.h"

float	lerp(float a, float b, float f)
{
	return (a * (1.0 - f) + (b * f));
}

t_vec2	find_vector(t_game *game, float player_a)
{
	t_vec2	new_vec;

	new_vec.x = cos(player_a);
	new_vec.y = sin(player_a);
	return (new_vec);
}

t_vec2	find_collision_point(t_game *game, t_vec2 vec2)
{
	int	tile_dist;

	(void)game;
	vec2.x = 0;
	tile_dist = 0;
	return (vec2);
}

// 				|
// 				|	
// ______________