/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: liliu <liliu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 16:00:00 by liliu             #+#    #+#             */
/*   Updated: 2025/12/01 16:00:00 by liliu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_file_extension(char *filename, char *ext)
{
	char	*dot;

	if (!filename || !ext)
		return (0);
	dot = ft_strrchr(filename, '.');
	if (!dot || ft_strncmp(dot, ext, ft_strlen(ext)) != 0)
		return (0);
	return (1);
}

void	init_game(t_game *game)
{
	game->mlx = NULL;
	game->win = NULL;
	game->img = NULL;
	game->map = NULL;
	game->player = NULL;
	ft_memset(game->textures, 0, sizeof(game->textures));
	game->keys.w = 0;
	game->keys.a = 0;
	game->keys.s = 0;
	game->keys.d = 0;
	game->keys.left = 0;
	game->keys.right = 0;
}

static void	set_player_dir(t_player *p, char c)
{
	if (c == 'N')
	{
		p->dir_x = 0;
		p->dir_y = -1;
	}
	else if (c == 'S')
	{
		p->dir_x = 0;
		p->dir_y = 1;
	}
	else if (c == 'E')
	{
		p->dir_x = 1;
		p->dir_y = 0;
	}
	else if (c == 'W')
	{
		p->dir_x = -1;
		p->dir_y = 0;
	}
	p->plane_x = -p->dir_y * 0.66;
	p->plane_y = p->dir_x * 0.66;
}

static int	check_cell(t_game *game, int y, int x)
{
	char	c;

	c = game->map->grid[y][x];
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
	{
		game->player->x = x + 0.5;
		game->player->y = y + 0.5;
		set_player_dir(game->player, c);
		return (1);
	}
	return (0);
}

void	init_player_from_map(t_game *game)
{
	int	y;
	int	x;

	y = 0;
	while (y < game->map->height)
	{
		x = 0;
		while (game->map->grid[y][x])
		{
			if (check_cell(game, y, x))
				return ;
			x++;
		}
		y++;
	}
}
