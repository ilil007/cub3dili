/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: liliu <liliu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 21:56:29 by liliu             #+#    #+#             */
/*   Updated: 2025/11/29 19:28:34 by liliu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


t_map	*parse_map(char *filename)
{
	t_map *map;
	char **all_lines;
	int total_lines;
	int map_start;
	int map_count;

	all_lines = read_file_lines(filename, &total_lines);
	if (!all_lines)
		return (NULL);
	map = malloc(sizeof(t_map));
	if (!map)
		return (NULL);
	ft_memset(map, 0, sizeof(t_map));
	parse_textures(map, all_lines, &map_start);
	map_count = count_map_lines(all_lines, map_start);
	if (map_count == 0)
	{
		free(map);
		return (NULL);
	}
	map->grid = extract_map(all_lines, map_start, map_count);
	map->height = map_count;
	map->width = get_max_width(map->grid);
	map->floor_color = 0x404040;
	map->ceiling_color = 0x87CEEB;
	while (total_lines-- > 0)
		free(all_lines[total_lines]);
	free(all_lines);
	return (map);
}

// code a function for parsing colors and checking errors in the file

// step1: find "F " or "C " in the file
// step2: "jump spaces and tabs"
// step3: record what is not spaces and tabs
// step4: split by ','
// step5: check if there are 3 parts
// step6: check each part is 3 characters max and is digit only
// step7: convert to int and check range 0-255
// step8: store color in map->floor_color or ceiling_color