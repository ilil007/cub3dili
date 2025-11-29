/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cal_dra_range.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: liliu <liliu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 21:36:07 by liliu             #+#    #+#             */
/*   Updated: 2025/11/27 21:36:32 by liliu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	calc_draw_range(t_ray *ray, int *line_height,
				int *draw_start, int *draw_end)
{
	*line_height = (int)(SCREEN_HEIGHT / ray->distance);
	*draw_start = -(*line_height) / 2 + SCREEN_HEIGHT / 2;
	if (*draw_start < 0)
		*draw_start = 0;
	*draw_end = (*line_height) / 2 + SCREEN_HEIGHT / 2;
	if (*draw_end >= SCREEN_HEIGHT)
		*draw_end = SCREEN_HEIGHT - 1;
}
