
#include "../cub.h"

float sacar_x(float px, float py, float vx, float vy, float y)
{
	float x;

	x = (vx - px) * ((y - py) / (vy - py)) + px;
	return (x);
}

float sacar_y(float px, float py, float vx, float vy, float x)
{
	float y;

	y = (vy - py) * ((x - px) / (vx - px)) + py;
	return (y);
}



static void	render_wall(t_game *game, int x, int len, t_color color)
{
	int		i_y;
	int		size;

	i_y = 0;
	size = WINDOW_HEIGHT - len;
	while (i_y < WINDOW_HEIGHT)
	{
		if (i_y > size / 2 && i_y < WINDOW_HEIGHT - size / 2)
			put_pixel_to_image(game, x, i_y, color);
		i_y++;
	}
}
static void	wall_dir(t_game *game, int x, float dist)
{
	t_color color;

	if (dist < 0)
		return;
	if (dist > 1024)
		dist = 1024;
	if (game->ray.cosen < 0)
		game->ray.c_x += 1;
	if (game->ray.sen < 0)
		game->ray.c_y += 1;
	if ((int)game->ray.c_y % 64 == 0 && (int)game->ray.c_x % 64 == 0)
	{
		color.R = 0;
		color.G = 0;
		color.B = 0;
	}
	else if ((int)game->ray.c_y % 64 == 0)
	{
		if (game->ray.sen < 0)
			game->ray.c_y -= 1;
		if (game->ray.c_y > game->player.y)
			color  = game->n_color;
		else
			color = game->s_color;
	}
	else
	{
		if (game->ray.cosen < 0)
			game->ray.c_x -= 1;
		if (game->ray.c_x > game->player.x)
			color = game->w_color;
		else
			color = game->e_color;
	}

	//if ((int)game->ray.c_y % 64 == 0 || (int)game->ray.c_y % 63 == 0)
	//{
	//	if (game->ray.c_y > game->player.y)
	//		color  = game->n_color;
	//	else
	//		color = game->s_color;
	//}
	//else if ((int)game->ray.c_x % 64 == 0 || (int)game->ray.c_x % 63 == 0)
	//{
	//	if (game->ray.c_x > game->player.x)
	//		color = game->w_color;
	//	else
	//		color = game->e_color;
	//}
	render_wall(game, x, PLANK_CONST / dist, color);
}

static void	find_wall(t_game *game, float angle, float distorsion, int x)
{
	float	dist;

	game->ray.c_y = game->player.y;
	game->ray.c_x = game->player.x;
	game->ray.cosen = cos(angle * M_PI / 180);
	game->ray.sen = -sin(angle * M_PI / 180);
	while (game->ray.c_y < (game->max_y + 1) * 64 && game->ray.c_x < game->max_x * 64 && \
			game->ray.c_y > 0 && game->ray.c_x > 0)
	{
		if (game->map[(int)game->ray.c_y / 64][(int)game->ray.c_x / 64] == '1')
		{
			//game->ray.c_x = ((int)game->ray.c_y / 64) * 64;
			//game->ray.c_x = sacar_x(game->player.x, game->player.y, game->ray.c_x, game->ray.c_y, game->ray.c_x);
			dist = sqrt(pow(game->ray.c_x - game->player.x, 2.0) + pow(game->ray.c_y - game->player.y, 2.0)) * cos(distorsion * M_PI / 180);
			wall_dir(game, x, dist);
			break ;

		}
		/*if (game->map[(int)game->ray.c_y / 64][(int)game->ray.c_x / 64] == '1')
		{
			game->ray.c_y =
			game->ray.c_y = sacar_y(game->player.x, game->player.y, game->ray.c_x, game->ray.c_y, ((int)game->ray.c_x / 64) * 64);
			dist = sqrt(pow(game->ray.c_x - game->player.x, 2.0) + pow(game->ray.c_y - game->player.y, 2.0)) * cos(distorsion * M_PI / 180);
			wall_dir(game, x, dist);
			break ;
		}*/
		game->ray.c_y = game->ray.c_y + game->ray.sen;
		game->ray.c_x = game->ray.c_x + game->ray.cosen;
	}
}

void	render_raycast_v2(t_game *game)
{
	int		x;
	float	angle;
	float	diff;

	x = 0;
	while (x < WINDOW_WIDTH)
	{
		angle = lerp(game->player.a + 25, \
		game->player.a - 25, (float)x / (float)WINDOW_WIDTH);
		if (angle < 0)
			angle += 360;
		else if (angle >= 360)
			angle -= 360;
		diff = angle - game->player.a;
		find_wall(game, angle, diff, x);
		/*
			calcular pared
			calcular textura x
			calcular textuta y
		*/

		x++;
	}
	
}