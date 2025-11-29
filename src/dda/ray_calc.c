/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_calc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: liliu <liliu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 20:56:49 by liliu             #+#    #+#             */
/*   Updated: 2025/11/27 21:03:03 by liliu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	calculate_wall_distance(t_game *game, t_ray *ray)
{
	// 计算垂直距离
	if (ray->side == 0)
		ray->perp_wall_dist = (ray->map_x - game->player->x
				+ (1 - ray->step_x) / 2.0) / ray->dir_x;
	else
		ray->perp_wall_dist = (ray->map_y - game->player->y
				+ (1 - ray->step_y) / 2.0) / ray->dir_y;
	// 防止极小值
	if (ray->perp_wall_dist < 0.1)
		ray->perp_wall_dist = 0.1;
	ray->distance = ray->perp_wall_dist;
	// 确定墙类型
	if (ray->side == 0)
	{
		if (ray->step_x > 0)
			ray->wall_type = WALL_WEST;
		else
			ray->wall_type = WALL_EAST;
	}
	else
	{
		if (ray->step_y > 0)
			ray->wall_type = WALL_NORTH;
		else
			ray->wall_type = WALL_SOUTH;
	}
}

void	calculate_ray_direction(t_game *game, t_ray *ray, int x)
{
	ray->camera_x = 2 * x / (double)SCREEN_WIDTH - 1;
	ray->dir_x = game->player->dir_x + game->player->plane_x * ray->camera_x;
	ray->dir_y = game->player->dir_y + game->player->plane_y * ray->camera_x;
	ray->map_x = (int)game->player->x;
	ray->map_y = (int)game->player->y;
}

void	cast_ray(t_game *game, t_ray *ray)
{
	init_dda(game, ray);
	perform_dda(game, ray);
	calculate_wall_distance(game, ray);
}
