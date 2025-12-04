/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: liliu <liliu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 21:56:29 by liliu             #+#    #+#             */
/*   Updated: 2025/11/29 20:50:10 by liliu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_all_lines(char **lines, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		free(lines[i]);
		i++;
	}
	free(lines);
}

static t_map	*init_map_struct(char **all_lines, int total_lines)
{
	t_map	*map;

	map = malloc(sizeof(t_map));
	if (!map)
	{
		free_all_lines(all_lines, total_lines);
		return (NULL);
	}
	ft_memset(map, 0, sizeof(t_map));
	return (map);
}

static t_map	*parse_fail(char **lines, int total, t_map *map)
{
	free_all_lines(lines, total);
	free_map(map);
	return (NULL);
}

static int	parse_map_grid(t_map *map, char **all_lines, int map_start)
{
	int	map_count;

	map_count = count_map_lines(all_lines, map_start);
	if (map_count == 0)
		return (0);
	if (!check_no_content_after_map(all_lines, map_start, map_count))
		return (0);
	map->grid = extract_map(all_lines, map_start, map_count);
	map->height = map_count;
	map->width = get_max_width(map->grid);
	return (1);
}

t_map	*parse_map(char *filename)
{
	t_map	*map;
	char	**all_lines;
	int		total_lines;
	int		map_start;

	all_lines = read_file_lines(filename, &total_lines);
	if (!all_lines)
		return (NULL);
	map = init_map_struct(all_lines, total_lines);
	if (!map)
		return (NULL);
	if (!parse_textures(map, all_lines, &map_start))
		return (parse_fail(all_lines, total_lines, map));
	if (!parse_map_grid(map, all_lines, map_start))
		return (parse_fail(all_lines, total_lines, map));
	map->floor_color = 0x404040;
	map->ceiling_color = 0x87CEEB;
	if (!parse_colors(map, all_lines))
		return (parse_fail(all_lines, total_lines, map));
	free_all_lines(all_lines, total_lines);
	return (map);
}
