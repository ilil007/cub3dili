/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_ceiling_floor.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: liliu <liliu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 21:11:03 by liliu             #+#    #+#             */
/*   Updated: 2025/11/27 21:27:58 by liliu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	draw_ceiling(t_game *game, int x, int draw_start)
{
	int	y;

	y = 0;
	while (y < draw_start)
	{
		put_pixel(game->img, x, y, game->map->ceiling_color);
		y++;
	}
}

static void	draw_floor(t_game *game, int x, int draw_end)
{
	int	y;

	y = draw_end;
	while (y < SCREEN_HEIGHT)
	{
		put_pixel(game->img, x, y, game->map->floor_color);
		y++;
	}
}

void	draw_ceiling_floor(t_game *game, int x, int draw_start, int draw_end)
{
	draw_ceiling(game, x, draw_start);
	draw_floor(game, x, draw_end);
}
