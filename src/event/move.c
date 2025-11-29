/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: liliu <liliu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 21:48:12 by liliu             #+#    #+#             */
/*   Updated: 2025/11/27 21:48:41 by liliu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	move_forward(t_game *game)
{
	double	new_x;
	double	new_y;

	new_x = game->player->x + game->player->dir_x * MOVE_SPEED;
	new_y = game->player->y + game->player->dir_y * MOVE_SPEED;
	if (game->map->grid[(int)new_y][(int)game->player->x] != '1')
		game->player->y = new_y;
	if (game->map->grid[(int)game->player->y][(int)new_x] != '1')
		game->player->x = new_x;
}

void	move_backward(t_game *game)
{
	double	new_x;
	double	new_y;

	new_x = game->player->x - game->player->dir_x * MOVE_SPEED;
	new_y = game->player->y - game->player->dir_y * MOVE_SPEED;
	if (game->map->grid[(int)new_y][(int)game->player->x] != '1')
		game->player->y = new_y;
	if (game->map->grid[(int)game->player->y][(int)new_x] != '1')
		game->player->x = new_x;
}

void	move_left(t_game *game)
{
	double	new_x;
	double	new_y;

	new_x = game->player->x - game->player->plane_x * MOVE_SPEED;
	new_y = game->player->y - game->player->plane_y * MOVE_SPEED;
	if (game->map->grid[(int)new_y][(int)game->player->x] != '1')
		game->player->y = new_y;
	if (game->map->grid[(int)game->player->y][(int)new_x] != '1')
		game->player->x = new_x;
}

void	move_right(t_game *game)
{
	double	new_x;
	double	new_y;

	new_x = game->player->x + game->player->plane_x * MOVE_SPEED;
	new_y = game->player->y + game->player->plane_y * MOVE_SPEED;
	if (game->map->grid[(int)new_y][(int)game->player->x] != '1')
		game->player->y = new_y;
	if (game->map->grid[(int)game->player->y][(int)new_x] != '1')
		game->player->x = new_x;
}
