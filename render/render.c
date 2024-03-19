
#include "../cub.h"

static void	draw_minimap_tile(int x, int y, t_game *game, t_color white)
{
	int		i_x;
	int		i_y;
	t_color	black;
	t_color	red;

	black = get_color(0, 0, 0);
	red = get_color(255, 0, 0);
	i_y = 0;
	while (i_y < 10)
	{
		i_x = 0;
		while (i_x++ < 10)
		{
			if (game->map[y][x] == '1')
				put_pixel_to_image(game, i_x + 10 + (x * 10), \
				i_y + 10 + (y * 10), white);
			else if (game->map[y][x + 1] != '\0' )
				put_pixel_to_image(game, i_x + 10 + (x * 10), \
				i_y + 10 + (y * 10), black);
			if (y == (int)game->player.y / 64 && x == (int)game->player.x / 64)
				put_pixel_to_image(game, i_x + 10 + (x * 10), \
				i_y + 10 + (y * 10), red);
		}
		i_y++;
	}
}

static void	draw_minimap(t_game *game)
{
	int		x;
	int		y;
	t_color	white;

	y = 0;
	white = get_color(255, 255, 255);
	while (game->map[y])
	{
		x = 0;
		while (game->map[y][x])
		{
			draw_minimap_tile(x, y, game, white);
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
	draw_minimap(game);
	mlx_put_image_to_window(game->mlx, game->win, game->image, 0, 0);
	mlx_put_image_to_window(game->mlx, game->win, game->ui, \
	WINDOW_WIDTH / 2 - 422, WINDOW_HEIGHT - 152);
	return (0);
}
	//render_raycast(game);
