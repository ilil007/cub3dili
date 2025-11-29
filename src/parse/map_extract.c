/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_extract.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: liliu <liliu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 21:00:00 by liliu             #+#    #+#             */
/*   Updated: 2025/11/29 20:50:44 by liliu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	get_line_len(char *line)
{
	int	len;

	len = 0;
	while (line[len] && line[len] != '\n')
		len++;
	return (len);
}

int	get_map_max_width(char **lines, int start, int count)
{
	int	i;
	int	max;
	int	len;

	max = 0;
	i = 0;
	while (i < count)
	{
		len = get_line_len(lines[start + i]);
		if (len > max)
			max = len;
		i++;
	}
	return (max);
}

static void	fill_line(char *dst, char *src, int len, int max)
{
	int	j;

	j = 0;
	while (j < len)
	{
		if (src[j] == ' ')
			dst[j] = '1';
		else
			dst[j] = src[j];
		j++;
	}
	while (j < max)
		dst[j++] = '1';
	dst[j] = '\0';
}

char	*copy_map_line(char *line, int max)
{
	char	*row;
	int		len;

	len = get_line_len(line);
	row = malloc(max + 1);
	if (!row)
		return (NULL);
	fill_line(row, line, len, max);
	return (row);
}

char	**extract_map(char **lines, int start, int count)
{
	char	**map;
	int		i;
	int		max;

	if (count <= 0)
		return (NULL);
	max = get_map_max_width(lines, start, count);
	map = malloc(sizeof(char *) * (count + 1));
	if (!map)
		return (NULL);
	i = 0;
	while (i < count)
	{
		map[i] = copy_map_line(lines[start + i], max);
		if (!map[i])
		{
			while (i > 0)
				free(map[--i]);
			return (free(map), NULL);
		}
		i++;
	}
	map[i] = NULL;
	return (map);
}
