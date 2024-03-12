/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgil-moy <sgil-moy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 13:23:13 by sgil-moy          #+#    #+#             */
/*   Updated: 2024/03/12 16:28:37 by sgil-moy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	leaks()
{
	system("leaks -q cub3d");
}

void	exit_game(t_game *game)
{
	//free_map(scene->map.map);
	mlx_destroy_window(game->mlx, game->win);
	mlx_destroy_image(game->mlx, game->image);
	exit(1);
}

int	main(int argc, char **argv)
{
	t_game	game;

	atexit(leaks);
	if (argc != 2)
		return (printf("BAD INPUT\n"), 1);
	parse(argv[1], &game);

	game.image = mlx_new_image(game.mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	game.mlx = mlx_init();
	game.win = mlx_new_window(game.mlx, WINDOW_WIDTH, WINDOW_HEIGHT, "joego pero muuy guapo");

	mlx_hook(game.win, 2, 0, key_hook, &game);
	mlx_hook(game.win, 6, 0, mouse_hook, &game);
	mlx_hook(game.win, 17, 0, close_win, &game);
	mlx_loop_hook(game.mlx, render, &game);
	mlx_loop(game.mlx);

	exit (0);
}
