/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_wall_loop.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: liliu <liliu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 21:37:00 by liliu             #+#    #+#             */
/*   Updated: 2025/12/01 15:43:20 by liliu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	init_wall_draw(t_ray *ray, t_texture *tex, double *s, double *tp)
{
	*s = 1.0 * tex->height / ray->line_height;
	*tp = (ray->draw_start - SCREEN_HEIGHT / 2 + ray->line_height / 2) * *s;
}

void	draw_wall_loop(t_game *game, t_ray *ray, int x, t_texture *tex)
{
	double	step;
	double	tex_pos;
	int		y;
	int		color;

	init_wall_draw(ray, tex, &step, &tex_pos);
	y = ray->draw_start;
	while (y < ray->draw_end)
	{
		color = get_texture_color(tex, calc_tex_x(ray, tex, game->player),
				calc_tex_y(&tex_pos, tex, step));
		put_pixel(game->img, x, y, get_shaded_color(ray, color));
		y++;
	}
}
