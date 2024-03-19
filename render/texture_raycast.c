
#include "../cub.h"

static void	render_wall(t_game *game, int x, int len, float dist)
{
	float		i_y;
	float		size;
	int			lerp_val;

	size = WINDOW_HEIGHT - len;
	i_y = size / 2;
	while (i_y < WINDOW_HEIGHT - size / 2)
	{
		lerp_val = 63 * ((i_y - (size / 2))  / (WINDOW_HEIGHT - (size)));
		if (lerp_val > 63)
			lerp_val = 63;
		if (lerp_val < 0)
			lerp_val = 0;
		t_color color = pixel_on_img(dist, lerp_val, game->n_tex);
		if (i_y < WINDOW_HEIGHT && i_y > -1)
		put_pixel_to_image(game, x, i_y, color);
		i_y++;
		if (i_y < -PLANK_CONST)
			break ;
	}
}

static void	wall_dir(t_game *game, int x, float dist)
{
	//t_color color;
	float aux;

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
		//color.R = 0;
		//color.G = 0;
		//color.B = 0;
	}
	else if ((int)game->ray.c_y % 64 == 0)
	{
		if (game->ray.sen < 0)
			game->ray.c_y -= 1;
		//if (game->ray.c_y > game->player.y)
		//	color  = game->n_color;
		//else
		//	color = game->s_color;
		aux = (int)game->ray.c_x % 64;
	}
	else
	{
		if (game->ray.cosen < 0)
			game->ray.c_x -= 1;
		//if (game->ray.c_x > game->player.x)
		//	color = game->w_color;
		//else
		//	color = game->e_color;
		aux = (int)game->ray.c_y % 64;
	}
	render_wall(game, x, PLANK_CONST / dist, aux);
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
			dist = sqrt(pow(game->ray.c_x - game->player.x, 2.0) + pow(game->ray.c_y - game->player.y, 2.0)) * cos(distorsion * M_PI / 180);
			wall_dir(game, x, dist);
			break ;

		}
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
		x++;
	}
}