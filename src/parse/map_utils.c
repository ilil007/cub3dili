/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: liliu <liliu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 21:55:46 by liliu             #+#    #+#             */
/*   Updated: 2025/11/29 20:50:48 by liliu            ###   ########.fr       */
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

int	check_no_content_after_map(char **lines, int map_start, int map_count)
{
	int		i;
	char	*p;

	i = map_start + map_count;
	while (lines[i])
	{
		p = lines[i];
		while (*p && (*p == ' ' || *p == '\t' || *p == '\n'))
			p++;
		if (*p && *p != '\n' && *p != '\0')
			return (0);
		i++;
	}
	return (1);
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
