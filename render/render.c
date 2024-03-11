
#include "../cub.h"

unsigned long createRGB(int r, int g, int b)
{   
    return ((r & 0xff) << 16) + ((g & 0xff) << 8) + (b & 0xff);
}

static void	draw_minimap_tile(int x, int y, t_game *game)
{
	int	i_x;
	int	i_y;

	i_y = 0;
	while (i_y < 64)
	{
		i_x = 0;
		while (i_x < 64)
		{
			if (game->map[y][x] == '1')
				mlx_pixel_put(game->mlx, game->win, i_x + 10 + (x * 10), \
				i_y + 10 + (y * 10), createRGB(255, 255, 255));
			else if (game->map[y][x] == '0')
				mlx_pixel_put(game->mlx, game->win, i_x + 10 + (x * 10), \
				i_y + 10 + (y * 10), createRGB(0, 0, 0));
			else if (game->map[y][x] != ' ')
				mlx_pixel_put(game->mlx, game->win, i_x + 10 + (x * 10), \
				i_y + 10 + (y * 10), createRGB(255, 0, 0));
			i_x++;
		}
		i_y++;
	}
}

static void	draw_minimap(t_game *game)
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


void put_pixel_to_image(t_game *game, int x, int y,t_color color)
{
	int	bits_per_pixel;
	int	size_line;
	int	endian;
	int color_rojo = 0x0000FF;

    char *image = mlx_get_data_addr(game->image, &bits_per_pixel, &size_line, &endian);
    int pixel_position = (y * size_line) + (x * (bits_per_pixel / 8));

    image[pixel_position + 2] = (createRGB(color.R, color.G, color.B) & 0xFF0000) >> 16;
    image[pixel_position + 1] = (createRGB(color.R, color.G, color.B) & 0x00FF00) >> 8;
    image[pixel_position] = createRGB(color.R, color.G, color.B) & 0x0000FF;
}

static void	draw_bg(t_game *game)
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
				put_pixel_to_image(game, x, y, game->celing_color);
			else
				put_pixel_to_image(game, x, y, game->floor_color);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(game->mlx, game->win, game->image, 0, 0);
}

int	render(t_game *game)
{
	(void)game;
	draw_bg(game);
	render_raycast(game);
	//draw_minimap(game);
	return (0);
}
