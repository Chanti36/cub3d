
#include "../cub.h"

unsigned long createRGB(int r, int g, int b)
{
	return ((r & 0xff) << 16) + ((g & 0xff) << 8) + (b & 0xff);
}

void put_pixel_to_image(t_game *game, int x, int y, t_color color)
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

t_color	pixel_on_img(int x, int y, void *img)
{
	//t_color	pingo;

	//pingo.R = img[y * 64 + x * 32 / 8 + 2];
	//pingo.G = img[y * 64 + x * 32 / 8 + 1];
	//pingo.B = img[y * 64 + x * 32 / 8];
	//return (pingo);

	t_color color;

	int	bits_per_pixel;
	int	size_line;
	int	endian;
	

	char *image = mlx_get_data_addr(img, &bits_per_pixel, &size_line, &endian);
	if (!image)
		printf("dsad\n");
		
	int pixel_position = (y * size_line) + (x * (bits_per_pixel / 8));

	color.R = image[pixel_position + 2];
	color.B = image[pixel_position + 1];
	color.G = image[pixel_position];
	return (color);
}

static void	draw_minimap_tile(int x, int y, t_game *game)
{
	int	i_x;
	int	i_y;
	t_color white;
	t_color black;
	t_color red;

	white.R = 255;
	white.G = 255;
	white.B = 255;
	black.R = 0;
	black.G = 0;
	black.B = 0;
	red.R = 255;
	red.G = 0;
	red.B = 0;


	i_y = 0;
	while (i_y < 10)
	{
		i_x = 0;
		while (i_x < 10)
		{
			if (game->map[y][x] == '1')
				put_pixel_to_image(game, i_x + 10 + (x * 10), i_y + 10 + (y * 10), white);
			else if (game->map[y][x + 1] != '\0' )//HARCODEAO
				put_pixel_to_image(game, i_x + 10 + (x * 10), i_y + 10 + (y * 10), black);
			if (y == (int)game->player.y / 64 && x == (int)game->player.x / 64)
				put_pixel_to_image(game, i_x + 10 + (x * 10), i_y + 10 + (y * 10), red);
			//put_pixel_to_image(game, game->player.x / 64 + 10, game->player.y / 64 + 10, red);
			i_x++;
		}
		i_y++;
	}
}

static void	draw_minimap(t_game *game)
{
	int	x;
	int	y;

	t_color red;
	red.R = 255;
	red.G = 0;
	red.B = 0;

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

static void	draw_bg(t_game *game)
{
	int	x;
	int	y;

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
}

int	render(t_game *game)
{
	update(game);

	mlx_clear_window(game->mlx, game->win);
	draw_bg(game);
	render_raycast_v2(game);
	//render_raycast(game);
	draw_minimap(game);
	mlx_put_image_to_window(game->mlx, game->win, game->image, 0, 0);
	mlx_put_image_to_window(game->mlx, game->win, game->ui, WINDOW_WIDTH / 2 - 422, WINDOW_HEIGHT - 152);
	return (0);
}
