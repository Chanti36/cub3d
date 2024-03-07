
#include "cub.h"

//int	can_move(t_game *game, int dir)
//{
//	int	x;
//	int	y;

//	x = game->player.x;
//	y = game->player.y;
//	if (dir == 0)
//		y -= 1;
//	if (dir == 1)
//	{
//		game->player.dir = -1;
//		x -= 1;
//	}
//	if (dir == 2)
//		y += 1;
//	if (dir == 3)
//	{
//		game->player.dir = 1;
//		x += 1;
//	}
//	if (game->map.map[y][x] == '1' ||
//		//game->map.map[y][x] == '!' ||
//		(game->map.map[y][x] == 'E' &&
//		game->map.can_exit != 1))
//		return (-1);
//	return (0);
//}

void	move(t_game *game, int dir)
{
	dir = 0;
	(void)game;	
}

int	key_hook(int keycode, t_game *game)
{
	if (keycode == KEY_W || keycode == KEY_UP)
		move(game, 0);
	if (keycode == KEY_A || keycode == KEY_LEFT)
		move(game, 1);
	if (keycode == KEY_S || keycode == KEY_DOWN)
		move(game, 2);
	if (keycode == KEY_D || keycode == KEY_RIGHT)
		move(game, 3);
	if (keycode == KEY_ESCAPE)
		exit(0);
		exit_game(game);
	return (0);
}

int	close_win(t_game *game)
{
	exit_game(game);
	return(0);
}
