/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: liliu <liliu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 21:55:46 by liliu             #+#    #+#             */
/*   Updated: 2025/11/29 15:09:24 by liliu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_map_line(char *line)
{
	int	i;

	if (!line || !line[0])
		return (0);
	i = 0;
	while (line[i] && line[i] != '\n')
	{
		if (line[i] != '0' && line[i] != '1' && line[i] != ' '
			&& line[i] != 'N' && line[i] != 'S'
			&& line[i] != 'E' && line[i] != 'W')
			return (0);
		i++;
	}
	return (i > 0);
}

int	count_map_lines(char **lines, int start)
{
	int	count;

	count = 0;
	while (lines[start + count] && is_map_line(lines[start + count]))
		count++;
	return (count);
}

int	get_max_width(char **grid)
{
	int	i;
	int	max;
	int	len;

	i = 0;
	max = 0;
	while (grid && grid[i])
	{
		len = ft_strlen(grid[i]);
		if (len > 0 && grid[i][len - 1] == '\n')
			len--;
		if (len > max)
			max = len;
		i++;
	}
	return (max);
}

char	**extract_map(char **lines, int start, int count)
{
	char    **map;
	int     i;
	int     j;
	int     max;
	int     len;
	char    *src;
	char    *p;

	if (count <= 0)
		return (NULL);
	max = 0;
	i = 0;
	while (i < count)
	{
		src = lines[start + i];
		p = (char *)src;
		while (*p == ' ' || *p == '\t')
			p++;
		len = 0;
		while (p[len] && p[len] != '\n')
			len++;
		if (len > max)
			max = len;
		i++;
	}
	map = malloc(sizeof(char *) * (count + 1));
	if (!map)
		return (NULL);
	i = 0;
	while (i < count)
	{
		src = lines[start + i];
		p = (char *)src;
		while (*p == ' ' || *p == '\t')
			p++;
		len = 0;
		while (p[len] && p[len] != '\n')
			len++;
		map[i] = malloc(max + 1);
		if (!map[i])
		{
			while (i > 0)
				free(map[--i]);
			return (free(map), NULL);
		}
		j = 0;
		while (j < len)
		{
			if (p[j] == ' ')
				map[i][j] = '1';
			else
				map[i][j] = p[j];
			j++;
		}
		while (j < max)
			map[i][j++] = '1';
		map[i][j] = '\0';
		i++;
	}
	map[i] = NULL;
	return (map);
}
