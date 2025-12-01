/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: liliu <liliu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 10:21:56 by hanchen           #+#    #+#             */
/*   Updated: 2025/12/01 15:47:42 by liliu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	setup_game(t_game *game, char *mapfile)
{
	game->map = parse_map(mapfile);
	if (!game->map)
		return (0);
	if (!validate_map(game->map))
		return (0);
	game->player = malloc(sizeof(t_player));
	if (!game->player)
		return (0);
	init_player_from_map(game);
	if (!texture_files_valid(game->map))
		return (0);
	return (1);
}

static int	start_game(t_game *game)
{
	if (!init_mlx(game))
		return (0);
	if (!load_textures(game))
		return (0);
	setup_hooks(game);
	mlx_loop(game->mlx);
	return (1);
}

int	main(int ac, char **av)
{
	t_game	game;

	if (ac != 2)
		error_exit("Error\nUsage: ./cub3d map.cub");
	if (!check_file_extension(av[1], ".cub"))
		error_exit("Error\nInvalid file extension");
	init_game(&game);
	if (!setup_game(&game, av[1]))
		error_exit("Error\nFailed to load game");
	if (!start_game(&game))
		error_exit("Error\nFailed to start game");
	cleanup_game(&game);
	return (0);
}
