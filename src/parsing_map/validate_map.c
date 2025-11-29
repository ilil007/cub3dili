/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: liliu <liliu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 22:10:48 by liliu             #+#    #+#             */
/*   Updated: 2025/11/27 22:17:15 by liliu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	validate_map(t_map *map)
{
	int		px;
	int		py;
	char	dir;

	if (!map || !map->grid)
		return (0);
	if (map->height < 3)
		return (0);
	if (!check_chars(map))
		return (0);
	if (!find_player(map, &px, &py, &dir))
		return (0);
	if (!check_walls(map))
		return (0);
	return (1);
}
