/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_position.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: liliu <liliu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 22:10:52 by liliu             #+#    #+#             */
/*   Updated: 2025/11/27 22:13:00 by liliu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	find_player(t_map *map, int *px, int *py, char *dir)
{
	int		y;
	int		x;
	int		count;
	char	c;

	y = 0;
	count = 0;
	while (y < map->height)
	{
		x = 0;
		while (map->grid[y][x])
		{
			c = map->grid[y][x];
			if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
			{
				*px = x;
				*py = y;
				*dir = c;
				count++;
			}
			x++;
		}
		y++;
	}
	return (count == 1);
}
