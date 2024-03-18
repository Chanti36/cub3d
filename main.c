
#include "cub.h"

void	leaks()
{
	system("leaks -q cub3d");
}

void	exit_game(t_game *game)
{
	mlx_destroy_window(game->mlx, game->win);
	mlx_destroy_image(game->mlx, game->image);
	mlx_destroy_image(game->mlx, game->ui);
	exit(1);
}

static void initialize(t_game *game)
{
	game->player.max_speed = 15;
	game->player.speed = 0;
	game->player.v_speed = 0;
}

int	main(int argc, char **argv)
{
	t_game	game;
	int size = 1080;

	atexit(leaks);
	if (argc != 2)
		return (printf("BAD INPUT\n"), 1);
	parse(argv[1], &game);
	initialize(&game);

	game.mlx = mlx_init();
	game.image = mlx_new_image(game.mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	game.win = mlx_new_window(game.mlx, WINDOW_WIDTH, WINDOW_HEIGHT, "joego pero muuy guapo");

	game.ui = mlx_xpm_file_to_image(game.mlx, "textures/ui.xpm", &size, &size);
	mlx_mouse_move(game.win, WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
	mlx_mouse_hide();
	mlx_do_sync(game.mlx);
	mlx_hook(game.win, 2, 0, key_hook, &game);
	mlx_hook(game.win, 6, 0, mouse_hook, &game);
	mlx_hook(game.win, 17, 0, close_win, &game);
	mlx_loop_hook(game.mlx, render, &game);
	mlx_loop(game.mlx);

	exit (0);
}
