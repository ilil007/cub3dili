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
	calc_draw_range(ray);
	draw_ceiling_floor(game, x, ray->draw_start, ray->draw_end);
	draw_wall_loop(game, ray, x, texture);
}
