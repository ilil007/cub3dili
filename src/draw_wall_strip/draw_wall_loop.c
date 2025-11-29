/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_wall_loop.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: liliu <liliu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 21:37:00 by liliu             #+#    #+#             */
/*   Updated: 2025/11/29 21:13:05 by liliu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

//draw_wall_strip(game, &ray, x);
void	draw_wall_loop(t_game *game, t_ray *ray, int x, \
				t_texture *texture, int draw_start, \
				int draw_end, int line_height)
{
	double	step;
	double	tex_pos;
	int		y;
	int		tex_y;
	int		tex_x;
	int		color;

	step = 1.0 * texture->height / line_height;
	tex_pos = (draw_start - SCREEN_HEIGHT / 2 + line_height / 2) * step;
	y = draw_start;
	while (y < draw_end)
	{
		tex_y = calc_tex_y(&tex_pos, texture, step);
		tex_x = calc_tex_x(ray, texture, game->player);
		color = get_shaded_color(ray, get_texture_color(texture, tex_x, tex_y));
		put_pixel(game->img, x, y, color);
		y++;
	}
}
