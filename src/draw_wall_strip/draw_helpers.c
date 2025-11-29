/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_helpers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: liliu <liliu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 21:28:38 by liliu             #+#    #+#             */
/*   Updated: 2025/11/29 21:13:46 by liliu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <math.h>

t_texture	*select_texture(t_game *game, t_ray *ray)
{
	if (ray->wall_type == WALL_NORTH)
		return (&game->textures[TEX_NO]);
	if (ray->wall_type == WALL_SOUTH)
		return (&game->textures[TEX_SO]);
	if (ray->wall_type == WALL_EAST)
		return (&game->textures[TEX_EA]);
	return (&game->textures[TEX_WE]);
}

int	calc_tex_x(t_ray *ray, t_texture *texture, t_player *player)
{
	double	wall_x;
	int		tex_x;

	if (ray->side == 0)
		wall_x = player->y + ray->distance * ray->dir_y;
	else
		wall_x = player->x + ray->distance * ray->dir_x;
	wall_x -= floor(wall_x);
	tex_x = (int)(wall_x * (double)texture->width);
	if ((ray->side == 0 && ray->dir_x > 0)
		|| (ray->side == 1 && ray->dir_y < 0))
		tex_x = texture->width - tex_x - 1;
	if (tex_x < 0)
		tex_x = 0;
	if (tex_x >= texture->width)
		tex_x = texture->width - 1;
	return (tex_x);
}

int	calc_tex_y(double *tex_pos, t_texture *texture, double step)
{
	int	tex_y;

	tex_y = (int)(*tex_pos);
	if (tex_y < 0)
		tex_y = 0;
	if (tex_y >= texture->height)
		tex_y = texture->height - 1;
	*tex_pos += step;
	return (tex_y);
}

int	get_shaded_color(t_ray *ray, int color)
{
	if (ray->side == 1)
		color = (color >> 1) & 0x7F7F7F;
	return (color);
}
