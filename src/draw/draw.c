/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: liliu <liliu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 14:22:36 by liliu             #+#    #+#             */
/*   Updated: 2025/11/29 14:22:40 by liliu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	put_pixel(t_img *img, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= SCREEN_WIDTH || y < 0 || y >= SCREEN_HEIGHT)
		return ;
	dst = img->addr + (y * img->line_len + x * (img->bpp / 8));
	*(unsigned int *)dst = (unsigned int)color;
}

int	get_texture_color(t_texture *texture, int tx, int ty)
{
	char	*pixel;
	int		color;

	if (!texture || !texture->addr)
	{
		printf("ERROR: Texture or addr is NULL\n");
		return (0xFF00FF);
	}
	if (tx < 0 || tx >= texture->width || ty < 0 || ty >= texture->height)
	{
		printf("ERROR: Texture coords out of bounds: (%d, %d) size: %dx%d\n",
			tx, ty, texture->width, texture->height);
		return (0x00FF00);
	}
	pixel = texture->addr + (ty * texture->line_len + tx * (texture->bpp / 8));
	color = *(unsigned int *)pixel;
	return (color);
}

void	clear_image(t_img *img)
{
	int	i;

	if (!img || !img->addr)
		return ;
	i = 0;
	while (i < SCREEN_WIDTH * SCREEN_HEIGHT)
	{
		((unsigned int *)img->addr)[i] = 0;
		i++;
	}
}
