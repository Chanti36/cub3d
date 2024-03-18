
#include "../cub.h"

static float	find_wall(t_game *game, float angle, float distorsion)
{
	float	i;
	float	j;
	float	cosen;
	float	sen;

	i = game->player.y;
	j = game->player.x;
	cosen = cos(angle * M_PI / 180);
	sen = -sin(angle * M_PI / 180);
	while (i < (game->max_y + 1) * 64 && j < game->max_x * 64 && i > 0 && j > 0)
	{
		if (game->map[(int)i / 64][(int)j / 64] == '1')
			return (sqrt(pow(j - game->player.x, 2.0) + pow(i - game->player.y, 2.0)) * cos(distorsion * M_PI / 180));
		i = i + sen;
		j = j + cosen;
	}
	return(-1);
}

static void	render_wall(t_game *game, int x, int len)
{
	t_color	wall_color;
	int		i_y;
	int		size;

	i_y = 0;
	wall_color.R = 130;
	wall_color.G = 240;
	wall_color.B = 80;
	size = WINDOW_HEIGHT - len;
	while (i_y < WINDOW_HEIGHT)
	{
		if (i_y > size / 2 && i_y < WINDOW_HEIGHT - size / 2)
			put_pixel_to_image(game, x, i_y, wall_color);
		i_y++;
	}
}

void	render_raycast(t_game *game)
{
	int		x;
	float	angle;
	float	dist;
	int angle_lerp;

	x = 0;
	while (x < WINDOW_WIDTH)
	{
		angle = lerp(game->player.a + 25, \
		game->player.a - 25, (float)x / (float)WINDOW_WIDTH);
		if (angle < 0)
			angle += 360;
		else if (angle >= 360)
			angle -= 360;
		float diff = angle - game->player.a;
		if (diff < 0)
			diff *=-1;
		dist = find_wall(game, angle, diff);
		if (dist >= 0)
		{
			if (dist > 1024)
				dist = 1024;
			render_wall(game, x, PLANK_CONST / dist);
		}
		x++;
	}
}
