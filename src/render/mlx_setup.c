/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_setup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: liliu <liliu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 22:21:12 by liliu             #+#    #+#             */
/*   Updated: 2025/11/27 22:21:29 by liliu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdio.h>
#include <stdlib.h>

int	init_mlx(t_game *game)
{
	printf("Initializing MLX...\n");
	game->mlx = mlx_init();
	if (!game->mlx)
		return (0);
	game->win = mlx_new_window(game->mlx, SCREEN_WIDTH, SCREEN_HEIGHT, "Cub3D");
	if (!game->win)
		return (0);
	game->img = malloc(sizeof(t_img));
	if (!game->img)
		return (0);
	game->img->img = mlx_new_image(game->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	if (!game->img->img)
		return (0);
	game->img->addr = mlx_get_data_addr(game->img->img, &game->img->bpp,
			&game->img->line_len, &game->img->endian);
	game->img->width = SCREEN_WIDTH;
	game->img->height = SCREEN_HEIGHT;
	printf("MLX initialized: %dx%d\n", SCREEN_WIDTH, SCREEN_HEIGHT);
	return (1);
}

void	setup_hooks(t_game *game)
{
	printf("Setting up hooks...\n");
	printf("Window pointer: %p\n", game->win);
	mlx_hook(game->win, KEY_PRESS, 1L << 0, handle_keypress, game);
	mlx_hook(game->win, KEY_RELEASE, 1L << 1, handle_keyrelease, game);
	mlx_hook(game->win, CLOSE_WINDOW, 0, close_game, game);
	mlx_loop_hook(game->mlx, game_loop, game);
	printf("Hooks set up successfully\n");
}

int	game_loop(t_game *game)
{
	update_player(game);
	clear_image(game->img);
	render_frame(game);
	mlx_put_image_to_window(game->mlx, game->win, game->img->img, 0, 0);
	return (0);
}
