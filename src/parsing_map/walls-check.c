/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   walls-check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: liliu <liliu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 22:11:00 by liliu             #+#    #+#             */
/*   Updated: 2025/11/27 23:28:13 by liliu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <string.h>
#include <stdio.h>

// Helper: check if a map cell is on edge or next to space/newline
int	check_cell_edges(char **grid, int y, int x, int height)
{
	if (y == 0 || y == height - 1)
		return (0);
	if (x == 0 || !grid[y][x + 1] || grid[y][x + 1] == '\n')
		return (0);
	if (x > 0 && grid[y][x - 1] == ' ')
		return (0);
	if (grid[y][x + 1] == ' ')
		return (0);
	if (y > 0 && x < (int)ft_strlen(grid[y - 1]) && grid[y - 1][x] == ' ')
		return (0);
	if (y < height - 1 && x < (int)ft_strlen(grid[y + 1]) \
		&& grid[y + 1][x] == ' ')
		return (0);
	return (1);
}

// Main wall check function
int	check_walls(t_map *map)
{
	int	y;
	int	x;

	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (map->grid[y][x] && map->grid[y][x] != '\n')
		{
			if (map->grid[y][x] == '0' || map->grid[y][x] == 'N'
				|| map->grid[y][x] == 'S' || map->grid[y][x] == 'E'
				|| map->grid[y][x] == 'W')
			{
				if (!check_cell_edges(map->grid, y, x, map->height))
					return (0);
			}
			x++;
		}
		y++;
	}
	return (1);
}
