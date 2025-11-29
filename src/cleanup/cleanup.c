/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: liliu <liliu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 14:27:55 by liliu             #+#    #+#             */
/*   Updated: 2025/11/29 14:28:22 by liliu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_map(t_map *map)
{
	int	i;

	if (!map)
		return ;
	if (map->grid)
	{
		i = 0;
		while (i < map->height && map->grid[i])
		{
			free(map->grid[i]);
			i++;
		}
		free(map->grid);
	}
	free(map);
}

void	free_textures(t_game *game)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (game->textures[i].img)
			mlx_destroy_image(game->mlx, game->textures[i].img);
		game->textures[i].img = NULL;
		i++;
	}
}

void	cleanup_game(t_game *game)
{
	if (!game)
		return ;
	if (game->mlx)
	{
		if (game->img && game->img->img)
		{
			mlx_destroy_image(game->mlx, game->img->img);
			game->img->img = NULL;
		}
		free_textures(game);
		if (game->win)
		{
			mlx_destroy_window(game->mlx, game->win);
			game->win = NULL;
		}
		mlx_destroy_display(game->mlx);
		free(game->mlx);
		game->mlx = NULL;
	}
	if (game->img)
		free(game->img);
	if (game->map)
		free_map(game->map);
	if (game->player)
		free(game->player);
}
