/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_colors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: liliu <liliu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 21:00:00 by liliu             #+#    #+#             */
/*   Updated: 2025/11/29 20:55:57 by liliu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	is_valid_rgb_part(char *str)
{
	int	i;
	int	len;

	if (!str || !str[0])
		return (0);
	i = 0;
	while (str[i] == ' ' || str[i] == '\t')
		i++;
	len = 0;
	while (str[i + len] && str[i + len] != ' ' && str[i + len] != '\t'
		&& str[i + len] != '\n')
	{
		if (!ft_isdigit(str[i + len]))
			return (0);
		len++;
	}
	return (len > 0 && len <= 3);
}

static void	free_parts(char **parts)
{
	int	i;

	i = 0;
	while (parts[i])
		free(parts[i++]);
	free(parts);
}

static int	convert_rgb(char **parts, int *color)
{
	int	r;
	int	g;
	int	b;

	if (!is_valid_rgb_part(parts[0]) || !is_valid_rgb_part(parts[1])
		|| !is_valid_rgb_part(parts[2]))
		return (free_parts(parts), 0);
	r = ft_atoi(parts[0]);
	g = ft_atoi(parts[1]);
	b = ft_atoi(parts[2]);
	free_parts(parts);
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
		return (0);
	*color = (r << 16) | (g << 8) | b;
	return (1);
}

static int	parse_single_color(char *line, int *color)
{
	char	*start;
	char	**parts;

	start = line + 2;
	while (*start && (*start == ' ' || *start == '\t'))
		start++;
	parts = ft_split(start, ',');
	if (!parts || !parts[0] || !parts[1] || !parts[2] || parts[3])
	{
		if (parts)
			free_parts(parts);
		return (0);
	}
	return (convert_rgb(parts, color));
}

int	parse_colors(t_map *map, char **lines)
{
	int		i;
	char	*p;
	int		found;

	i = -1;
	found = 0;
	while (lines[++i])
	{
		p = lines[i];
		while (*p && (*p == ' ' || *p == '\t'))
			p++;
		if (ft_strncmp(p, "F ", 2) == 0)
		{
			if (!parse_single_color(p, &map->floor_color))
				return (0);
			found |= 1;
		}
		else if (ft_strncmp(p, "C ", 2) == 0)
		{
			if (!parse_single_color(p, &map->ceiling_color))
				return (0);
			found |= 2;
		}
	}
	return (found == 3);
}
