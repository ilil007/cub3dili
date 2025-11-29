/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_frame.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: liliu <liliu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 22:20:51 by liliu             #+#    #+#             */
/*   Updated: 2025/11/27 22:26:05 by liliu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdio.h>

static int	g_debug_frame = 0;

void	print_debug_info_first_frame(t_game *game)
{
	int	y;

	printf("\n=== DEBUG INFO (Frame 0) ===\n");
	printf("Player pos: (%.2f, %.2f)\n", game->player->x, game->player->y);
	printf("Player dir: (%.2f, %.2f)\n", game->player->dir_x, game->player->dir_y);
	printf("Player plane: (%.2f, %.2f)\n", game->player->plane_x, game->player->plane_y);
	printf("Map size: %d x %d\n", game->map->width, game->map->height);
	printf("Screen: %d x %d\n", SCREEN_WIDTH, SCREEN_HEIGHT);
	printf("\nFirst 5 rows of map:\n");
	y = 0;
	while (y < 5 && y < game->map->height)
	{
		printf("Row %d: [%s]\n", y, game->map->grid[y]);
		y++;
	}
	printf("...\n\n");
}

void	print_center_ray_debug(t_ray *ray)
{
	printf("Center ray:\n");
	printf("  camera_x: %.3f\n", ray->camera_x);
	printf("  ray dir: (%.3f, %.3f)\n", ray->dir_x, ray->dir_y);
	printf("  hit: %d at (%d, %d)\n", ray->hit, ray->map_x, ray->map_y);
	printf("  distance: %.2f\n", ray->distance);
	printf("  wall_type: %d, side: %d\n", ray->wall_type, ray->side);
}

void	render_frame(t_game *game)
{
	int		x;
	t_ray	ray;

	if (g_debug_frame == 0)
	{
		print_debug_info_first_frame(game);
		g_debug_frame = 1;
	}
	x = 0;
	while (x < SCREEN_WIDTH)
	{
		calculate_ray_direction(game, &ray, x);
		cast_ray(game, &ray);
		if (g_debug_frame == 1 && x == SCREEN_WIDTH / 2)
			print_center_ray_debug(&ray);
		draw_wall_strip(game, &ray, x);
		x++;
	}
	if (g_debug_frame == 1)
	{
		printf("\nFirst frame rendered successfully!\n");
		g_debug_frame = 2;
	}
}
