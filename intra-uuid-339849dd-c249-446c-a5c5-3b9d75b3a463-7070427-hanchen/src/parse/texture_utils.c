/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: liliu <liliu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 21:56:13 by liliu             #+#    #+#             */
/*   Updated: 2025/11/29 20:52:20 by liliu            ###   ########.fr       */
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

static int	set_texture(char **dst, char *line)
{
	if (*dst)
		return (0);
	*dst = parse_texture_path(line);
	return (1);
}

static int	parse_texture_line(t_map *map, char *line, char *p)
{
	if (ft_strncmp(p, "NO ", 3) == 0)
		return (set_texture(&map->n_texture, line));
	else if (ft_strncmp(p, "SO ", 3) == 0)
		return (set_texture(&map->s_texture, line));
	else if (ft_strncmp(p, "WE ", 3) == 0)
		return (set_texture(&map->w_texture, line));
	else if (ft_strncmp(p, "EA ", 3) == 0)
		return (set_texture(&map->e_texture, line));
	return (1);
}

static int	all_textures_set(t_map *map)
{
	if (!map->n_texture || !map->s_texture)
		return (0);
	if (!map->w_texture || !map->e_texture)
		return (0);
	return (1);
}

int	parse_textures(t_map *map, char **lines, int *map_start)
{
	int		i;
	char	*p;

	i = 0;
	*map_start = 0;
	while (lines[i])
	{
		p = lines[i];
		while (*p && (*p == ' ' || *p == '\t'))
			p++;
		if (is_map_line(lines[i]))
		{
			*map_start = i;
			break ;
		}
		if (!parse_texture_line(map, lines[i], p))
			return (0);
		i++;
	}
	return (all_textures_set(map));
}
