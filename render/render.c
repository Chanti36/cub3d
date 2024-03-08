
#include "../cub.h"

static int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

static void draw_minimap_tile(int x, int y, t_game *game)
{
	int	i_x;
	int	i_y;

	i_y = 0;
	while (i_y < 10)
	{
		i_x = 0;
		while (i_x < 10)
		{
			if (game->map[y][x] == '1')
				mlx_pixel_put(game->mlx, game->win, i_x + 10 + (x * 10), \
				i_y + 10 + (y * 10), create_trgb(0, 255, 255, 255));
			else if (game->map[y][x] == '0')
				mlx_pixel_put(game->mlx, game->win, i_x + 10 + (x * 10), \
				i_y + 10 + (y * 10), create_trgb(0, 0, 0, 0));
			else if (game->map[y][x] != ' ')
				mlx_pixel_put(game->mlx, game->win, i_x + 10 + (x * 10), \
				i_y + 10 + (y * 10), create_trgb(0, 255, 0, 0));
			i_x++;
		}
		i_y++;
	}
}

static void draw_minimap(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	while (game->map[y])
	{
		x = 0;
		while (game->map[y][x])
		{
			draw_minimap_tile(x, y, game);
			x++;
		}
		y++;
	}
}

static void draw_bg(t_game *game)
{
	int	x;
	int	y;
	
	mlx_clear_window(game->mlx, game->win);
	y = 0;
	while (y < WINDOW_HEIGHT)
	{
		x = 0;
		while (x < WINDOW_WIDTH)
		{
			if (y < WINDOW_HEIGHT / 2)
				mlx_pixel_put(game->mlx, game->win, x, y, create_trgb(0, game->celing_color.R, game->celing_color.G, game->celing_color.B));
			else
				mlx_pixel_put(game->mlx, game->win, x, y, create_trgb(0, game->floor_color.R, game->floor_color.G, game->floor_color.B));
			x++;
		}
		y++;
	}
}

int	render(t_game *game)
{
	draw_bg(game);
	render_raycast(game);
	draw_minimap(game);
	return  (0);
}
