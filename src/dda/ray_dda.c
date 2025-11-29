/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_dda.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: liliu <liliu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 20:56:32 by liliu             #+#    #+#             */
/*   Updated: 2025/11/27 20:57:13 by liliu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <string.h>

static int	check_hit(t_game *game, t_ray *ray)
{
	// 边界检查
	if (ray->map_x < 0 || ray->map_x >= game->map->width
		|| ray->map_y < 0 || ray->map_y >= game->map->height)
		return (1);
	// 检查行存在
	if (!game->map->grid[ray->map_y])
		return (1);
	// 检查行长度
	if (ray->map_x >= (int)ft_strlen(game->map->grid[ray->map_y]))
		return (1);
	// 检查墙
	if (game->map->grid[ray->map_y][ray->map_x] == '1')
		return (1);
	return (0);
}

void	perform_dda(t_game *game, t_ray *ray)
{
	int	steps;
	int	max_steps;

	max_steps = 100;
	steps = 0;
	ray->hit = 0;
	while (!ray->hit && steps < max_steps)
	{
		if (ray->side_dist_x < ray->side_dist_y)
		{
			ray->side_dist_x += ray->delta_dist_x;
			ray->map_x += ray->step_x;
			ray->side = 0;
		}
		else
		{
			ray->side_dist_y += ray->delta_dist_y;
			ray->map_y += ray->step_y;
			ray->side = 1;
		}
		ray->hit = check_hit(game, ray);
		steps++;
	}
}
