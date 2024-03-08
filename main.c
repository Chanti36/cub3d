/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgil-moy <sgil-moy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 13:23:13 by sgil-moy          #+#    #+#             */
/*   Updated: 2024/03/08 12:05:16 by sgil-moy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"


void leaks()
{
   system("leaks -q cub3d");
}

void	exit_game(t_game *game)
{
	//free_map(scene->map.map);
	mlx_destroy_window(game->mlx, game->win);
	exit(1);
}

int main(int argc, char **argv)
{
	t_game game;

	atexit(leaks);
	if (argc != 2)
		return (printf("BAD INPUT\n"), 1);
	parse(argv[1], &game);

	game.player.x = 27;
	game.player.y = 11;
	
	game.mlx = mlx_init();
	game.win = mlx_new_window(game.mlx, WINDOW_WIDTH, WINDOW_HEIGHT, "joego pero muuy guapo");
	mlx_hook(game.win, 2, 0, key_hook, &game);
	mlx_hook(game.win, 17, 0, close_win, &game);
	mlx_loop_hook(game.mlx, render, &game);
	mlx_loop(game.mlx);
	exit (0);
}
