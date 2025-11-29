/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: liliu <liliu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 21:56:13 by liliu             #+#    #+#             */
/*   Updated: 2025/11/29 17:23:28 by liliu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdlib.h>

char	*parse_texture_path(char *line)
{
	char	*path;
	int		i;
	int		start;
	int		len;

	i = 0;
	while (line[i] && (line[i] == ' ' || line[i] == '\t'))
		i++;
	while (line[i] && line[i] != ' ' && line[i] != '\t')
		i++;
	while (line[i] && (line[i] == ' ' || line[i] == '\t'))
		i++;
	start = i;
	while (line[i] && line[i] != ' ' && line[i] != '\t' && line[i] != '\n')
		i++;
	len = i - start;
	if (len == 0)
		return (NULL);
	path = malloc(len + 1);
	if (!path)
		return (NULL);
	ft_memcpy(path, line + start, len);
	path[len] = '\0';
	return (path);
}

void	parse_textures(t_map *map, char **lines, int *map_start)
{
	int	i;

	i = 0;
	*map_start = 0;
	while (lines[i])
	{
		char *p = lines[i];
		while (*p && (*p == ' ' || *p == '\t'))
			p++;
		if (ft_strncmp(p, "NO ", 3) == 0)
			map->n_texture = parse_texture_path(lines[i]);
		else if (ft_strncmp(p, "SO ", 3) == 0)
			map->s_texture = parse_texture_path(lines[i]);
		else if (ft_strncmp(p, "WE ", 3) == 0)
			map->w_texture = parse_texture_path(lines[i]);
		else if (ft_strncmp(p, "EA ", 3) == 0)
			map->e_texture = parse_texture_path(lines[i]);
		else if (is_map_line(lines[i]))
		{
			*map_start = i;
			break ;
		}
		i++;
	}
}

