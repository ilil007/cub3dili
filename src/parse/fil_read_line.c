/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fil_read_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: liliu <liliu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 22:01:03 by liliu             #+#    #+#             */
/*   Updated: 2025/11/29 15:21:34 by liliu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdlib.h>

char	**read_lines_from_fd(int fd, int *height)
{
	char	**lines;
	char	*line;
	int		i;
	int		capacity;

	capacity = 100;
	lines = malloc(sizeof(char *) * capacity);
	if (!lines)
		return (NULL);
	i = 0;
	line = get_next_line(fd);
	while (line)
	{
		if (i >= capacity - 1)
		{
			capacity *= 2;
			lines = realloc(lines, sizeof(char *) * capacity);
		}
		lines[i++] = line;
		line = get_next_line(fd);
	}
	lines[i] = NULL;
	*height = i;
	return (lines);
}

char	**read_file_lines(char *filename, int *height)
{
	int fd;
	char **lines;

	fd = open_file(filename);
	if (fd < 0)
		return (NULL);
	lines = read_lines_from_fd(fd, height);
	close(fd);
	return (lines);
}
