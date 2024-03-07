
#include "../cub.h"

static int space_in_perimeter(char **map, int x, int y)
{
	if (map[y-1][x-1] == ' ' || \
		map[y-1][x] == ' ' || \
		map[y-1][x+1] == ' ' || \
		map[y][x-1] == ' ' || \
		map[y][x] == ' ' || \
		map[y][x+1] == ' ' || \
		map[y+1][x-1] == ' ' || \
		map[y+1][x] == ' ' || \
		map[y+1][x+1] == ' ')
	{
		if (map[y][x] != '1' && map[y][x] != ' ')
			return (1);
	}
	return (0);
}

static void	check_perimeter(t_game *game, int x, int y)
{
	if (x == game->max_x || y == 0 || y == game->max_y || x == 0)
	{
		if (game->map[y][x] != '1' && game->map[y][x] != ' ')
		{
			printf ("ta mal2 %d %d", x, y);
			exit(1);
		}
	}
	else
	{
		if (space_in_perimeter(game->map, x, y))
		{
			printf ("ta mal1 %d %d", x, y);
			exit(1);
		}
	}
}

void check_map_walls(t_game *game)
{
	int	y;
	int	x;

	y = 0;
	printf("check map\n");
	while (game->map[y])
	{
		x = 0;
		while (game->map[y][x])
		{
			check_perimeter(game, x, y);
			x++;
		}
		y++;
	}

	printf("WALLs guxi\n");
}
