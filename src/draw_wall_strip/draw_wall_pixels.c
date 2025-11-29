/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_wall_pixels.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: liliu <liliu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 21:11:23 by liliu             #+#    #+#             */
/*   Updated: 2025/11/29 21:12:41 by liliu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_wall_pixels(t_game *game, t_ray *ray, int x, t_texture *texture)
{
	int	line_height;
	int	draw_start;
	int	draw_end;

	calc_draw_range(ray, &line_height, &draw_start, &draw_end);
	draw_ceiling_floor(game, x, draw_start, draw_end);
	draw_wall_loop(game, ray, x, texture, draw_start, draw_end, line_height);
}
