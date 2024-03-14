
#include "../cub.h"

void	*free_map(char **map)
{
	int	i;

	i = 0;
	while (map[i])
	{
		free(map[i]);
		i++;
	}
	free(map);
	return (NULL);
}

void	fill_map_line(t_gnl *str_map, char**new_map, int x, int i)
{
	int	j;
	int	flag;

	j = 0;
	flag = 0;
	while (j < x)
	{
		if (str_map->content[j] && str_map->content[j] != '\n' && flag != 1)
			new_map[i][j] = str_map->content[j];
		else
		{
			flag = 1;
			new_map[i][j] = ' ';
		}
		++j;
	}
	new_map[i][j] = '\0';
}

static char	**make_map(t_game *game, t_gnl *str_map, int x, int y)
{
	int		i;
	char	**new_map;

	i = 0;
	game->max_x = x - 1;
	game->max_y = y - 1;
	new_map = (char **)malloc(sizeof(char *) * y + 1);
	if (!new_map)
		return (NULL);
	while (i < y)
	{
		new_map[i] = (char *)malloc(sizeof(char) * (x + 1));
		if (!new_map[i])
			return (free_map(new_map));
		fill_map_line(str_map, new_map, x, i);
		++i;
		str_map = str_map->next;
	}
	new_map[i] = NULL;
	return (new_map);
}

static void	create_map(t_gnl *str_map, t_game *game)
{
	t_gnl	*i;
	int		x;
	int		y;
	int		len;

	x = 0;
	y = 0;
	i = str_map;
	while (i)
	{
		len = 0;
		while (i->content[len])
			len++;
		if (len > x)
			x = len;
		i = i->next;
		++y;
	}
	game->map = make_map(game, str_map, x, y);
}

static void	measure_map(t_gnl *str_map, t_game *game)
{
	t_gnl	*i;
	int		j;
	int		flag;

	i = str_map;
	while (i)
	{
		j = 0;
		flag = 0;
		while (i->content[j])
		{
			if (i->content[j] != '1' && i->content[j] != '0' && \
			i->content[j] != 'N' && i->content[j] != 'S' && \
			i->content[j] != 'E' && i->content[j] != 'W' && \
			i->content[j] != '\n' && i->content[j] != ' ')
				flag = 1;
			++j;
		}
		if (i->content[0] == '\n')
			flag = 1;
		if (!flag)
			break ;
		i = i->next;
	}
	create_map(i, game);
}

static void	check_map_char(t_game *game)
{
	int	i;
	int	j;
	int	flag;

	i = 0;
	flag = 0;
	while (game->map[i])
	{
		j = 0;
		while (game->map[i][j])
		{
			if (game->map[i][j] != '1' && game->map[i][j] != '0' && \
			game->map[i][j] != 'N' && game->map[i][j] != 'S' && \
			game->map[i][j] != 'E' && game->map[i][j] != 'W' && \
			game->map[i][j] != ' ')
			{
				printf("caracter invalido\n");
				exit (1);
			}
			if (game->map[i][j] == 'N' || game->map[i][j] == 'S' || \
				game->map[i][j] == 'E' || game->map[i][j] == 'W')
			{
				game->player.y = (i * 64) + 32;
				game->player.x = (j * 64) + 32;
				game->player.a = 90;
				if (flag)
				{
					printf("caracter de personaje repetido\n");
					exit (1);
				}
				flag = 1;
			}
			j++;
		}
		i++;
	}
}

void	check_map(t_gnl *str_map, t_game *game)
{
	int	x;
	int	y;

	y = 0;
	measure_map(str_map, game);
	printf("-------------------------asdasd---------------------\n");
	while (game->map[y])
	{
		x = 0;
		while (game->map[y][x])
		{
			printf("%c", game->map[y][x]);
			x++;
		}
		printf("\n");
		y++;
	}
	printf("-------------------------asdasd---------------------\n");
	check_map_char(game);
	check_map_walls(game);
	y = 0;
	while (y < game->max_y)
	{
		x = 0;
		while (x < game->max_x)
		{
			if (game->map[y][x] == ' ')
				game->map[y][x] = '0';
			x++;
		}
		y++;
	}
}
