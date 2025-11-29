/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_wall_strip.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: liliu <liliu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 22:50:00 by liliu             #+#    #+#             */
/*   Updated: 2025/11/27 22:47:22 by liliu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void    draw_wall_strip(t_game *game, t_ray *ray, int x)
{
	t_texture *texture;

	texture = select_texture(game, ray);
	draw_wall_pixels(game, ray, x, texture);
}
