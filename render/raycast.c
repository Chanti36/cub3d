
#include "../cub.h"

static float	find_wall(t_game *game, float angle)
{
	float	i;
	float	j;
	float	cosen;
	float	sino;

	cosen = cos(angle) / 10;
	sino = -sin(angle) / 10;
	//printf("angle: %f    cosen: %f\n", sino, cosen);
	j = game->player.x;
	i = game->player.y;

	while (1)
	{
		if ((int)floor(i) % 64 == 0)
		{
			if(game->map[(int)floor(i) / 64][(int)floor(j) / 64] == '1' || \
			game->map[(int)floor(i) / 64 + 1][(int)floor(j) / 64] == '1')
			{
				printf("x: %f         y:%f \n", j, i);
				//printf("x = %d y = %d, char = %c || char+1 = %c \n", 
				//(int)floor(j) / 64, 
				//(int)floor(i) / 64, 
				//game->map[(int)floor(i) / 64][(int)floor(j) / 64], 
				//game->map[(int)floor(i) / 64 + 1][(int)floor(j) / 64]);
				//return (((j - game->player.x) * 2) / (i - game->player.y));
				return (sqrt(((j - game->player.x) * (j - game->player.x)) + ((i - game->player.y) * (i - game->player.y))));
			}
		}
		if ((int)floor(j) % 64 == 0)
		{
			if (game->map[(int)floor(i) / 64][(int)floor(j) / 64] == '1' || \
			game->map[(int)floor(i) / 64][(int)floor(j) / 64 + 1] == '1')
			{
				printf("x: %f         y:%f \n", j, i);
					//printf("x = %d y = %d, char = %c || char+1 = %c \n",
					// (int)floor(j) / 64,
					//  (int)floor(i) / 64,
					//   game->map[(int)floor(i) / 64][(int)floor(j) / 64],
					//    game->map[(int)floor(i) / 64][(int)floor(j) / 64 + 1]);
					return (sqrt(((j - game->player.x) * (j - game->player.x)) + ((i - game->player.y) * (i - game->player.y))));
			}
		}
		i += sino;
		j += cosen;
	}
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
	int		size;
	int angle_lerp;


	//dist = find_wall(game, 45.1);
	//printf("dist = %f\n", dist);

	x = 0;
	while (x < WINDOW_WIDTH)
	{
		//angle_lerp = -45 + ((x / WINDOW_WIDTH) * 90);
		//angle = game->player.a + angle_lerp;

		angle = lerp(game->player.a + 5, \
		game->player.a - 5, (float)x / (float)WINDOW_WIDTH);
		if (angle < 0)
			angle += 360;
		else if (angle >= 360)
			angle -= 360;

		dist = find_wall(game, angle);
		if (dist != 0)
		{
			//printf("dist = %f\n", dist);
			size = lerp(WINDOW_HEIGHT, WINDOW_HEIGHT / 20, dist / WINDOW_HEIGHT);
			render_wall(game, x, dist);
		}
		x++;
	}
}
