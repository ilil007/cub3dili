/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: liliu <liliu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 16:00:00 by liliu             #+#    #+#             */
/*   Updated: 2025/12/01 16:00:00 by liliu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	load_single_texture(t_game *game, t_texture *tex, char *path)
{
	if (!path)
		return (0);
	tex->img = mlx_xpm_file_to_image(game->mlx, path,
			&tex->width, &tex->height);
	if (!tex->img)
		return (0);
	tex->addr = mlx_get_data_addr(tex->img, &tex->bpp,
			&tex->line_len, &tex->endian);
	return (1);
}

int	load_textures(t_game *game)
{
	if (!load_single_texture(game, &game->textures[TEX_NO],
			game->map->n_texture))
		return (0);
	if (!load_single_texture(game, &game->textures[TEX_SO],
			game->map->s_texture))
		return (0);
	if (!load_single_texture(game, &game->textures[TEX_EA],
			game->map->e_texture))
		return (0);
	if (!load_single_texture(game, &game->textures[TEX_WE],
			game->map->w_texture))
		return (0);
	return (1);
}

static int	check_tex_file(char *path)
{
	if (!check_file_extension(path, ".xpm"))
		return (0);
	if (access(path, R_OK) != 0)
		return (0);
	return (1);
}

int	texture_files_valid(t_map *map)
{
	if (!map)
		return (0);
	if (!check_tex_file(map->n_texture))
		return (0);
	if (!check_tex_file(map->s_texture))
		return (0);
	if (!check_tex_file(map->e_texture))
		return (0);
	if (!check_tex_file(map->w_texture))
		return (0);
	return (1);
}
