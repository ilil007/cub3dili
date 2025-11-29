/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: liliu <liliu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 10:21:56 by hanchen           #+#    #+#             */
/*   Updated: 2025/11/29 19:05:14 by liliu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* Check if filename has given extension */
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

/* Initialize player position and direction from map */
void	init_player_from_map(t_game *game)
{
	int		y;
	int		x;
	char	c;

	y = 0;
	while (y < game->map->height)
	{
		x = 0;
		while (game->map->grid[y][x])
		{
			c = game->map->grid[y][x];
			if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
			{
				game->player->x = x + 0.5;
				game->player->y = y + 0.5;
				if (c == 'N')
					game->player->dir_x = 0, game->player->dir_y = -1;
				else if (c == 'S')
					game->player->dir_x = 0, game->player->dir_y = 1;
				else if (c == 'E')
					game->player->dir_x = 1, game->player->dir_y = 0;
				else if (c == 'W')
					game->player->dir_x = -1, game->player->dir_y = 0;
				game->player->plane_x = -game->player->dir_y * 0.66;
				game->player->plane_y = game->player->dir_x * 0.66;
				return ;
			}
			x++;
		}
		y++;
	}
}

/* Initialize game struct */
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

/* Load a single texture */
int	load_single_texture(t_game *game, t_texture *tex, char *path)
{
	if (!path)
		return (0);
	tex->img = mlx_xpm_file_to_image(game->mlx, path, &tex->width, &tex->height);
	if (!tex->img)
		return (0);
	tex->addr = mlx_get_data_addr(tex->img, &tex->bpp, &tex->line_len, &tex->endian);
	return (1);
}

/* Load all four wall textures */
int	load_textures(t_game *game)
{
	if (!load_single_texture(game, &game->textures[TEX_NO], game->map->n_texture))
		return (0);
	if (!load_single_texture(game, &game->textures[TEX_SO], game->map->s_texture))
		return (0);
	if (!load_single_texture(game, &game->textures[TEX_EA], game->map->e_texture))
		return (0);
	if (!load_single_texture(game, &game->textures[TEX_WE], game->map->w_texture))
		return (0);
	return (1);
}

/* Verify texture file extension and readability without MLX */
int	texture_files_valid(t_map *map)
{
	if (!map)
		return (0);
	if (!check_file_extension(map->n_texture, ".xpm") || access(map->n_texture, R_OK) != 0)
		return (0);
	if (!check_file_extension(map->s_texture, ".xpm") || access(map->s_texture, R_OK) != 0)
		return (0);
	if (!check_file_extension(map->e_texture, ".xpm") || access(map->e_texture, R_OK) != 0)
		return (0);
	if (!check_file_extension(map->w_texture, ".xpm") || access(map->w_texture, R_OK) != 0)
		return (0);
	return (1);
}

/* Main entry */
int	main(int ac, char **av)
{
	t_game	game;

	if (ac != 2)
		error_exit("Error\nUsage: ./cub3d map.cub");
	if (!check_file_extension(av[1], ".cub"))
		error_exit("Error\nInvalid file extension");
	init_game(&game);
	game.map = parse_map(av[1]);
	if (!game.map)
		error_exit("Error\nFailed to parse map");
	if (!validate_map(game.map))
		error_exit("Error\nInvalid map");
	game.player = malloc(sizeof(t_player));
	if (!game.player)
		error_exit("Failed to allocate player");
	init_player_from_map(&game);
	/* Pre-check texture files before initializing MLX */
	if (!texture_files_valid(game.map))
		error_exit("Failed to load textures");
	if (!init_mlx(&game))
		error_exit("Failed to initialize MLX");
	if (!load_textures(&game))
		error_exit("Failed to load textures");
	setup_hooks(&game);
	mlx_loop(game.mlx);
	cleanup_game(&game);
	return (0);
}

