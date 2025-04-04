/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: habouda <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 02:31:44 by habouda           #+#    #+#             */
/*   Updated: 2025/04/04 19:18:11 by habouda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	rotate_left(t_cub *cub, double rotation_speed)
{
	double	new_dir_x;
	double	new_plane_x;

	new_dir_x = cub->player->dir_x;
	cub->player->dir_x = cub->player->dir_x * cos(-rotation_speed) - cub->player->dir_y
		* sin(-rotation_speed);
	cub->player->dir_y = new_dir_x * sin(-rotation_speed) + cub->player->dir_y
		* cos(-rotation_speed);
	new_plane_x = cub->player->plane_x;
	cub->player->plane_x = cub->player->plane_x * cos(-rotation_speed)
		- cub->player->plane_y * sin(-rotation_speed);
	cub->player->plane_y = new_plane_x * sin(-rotation_speed) + cub->player->plane_y
		* cos(-rotation_speed);
}

void	rotate_right(t_cub *cub, double rotation_speed)
{
	double	new_dir_x;
	double	new_plane_x;

	new_dir_x = cub->player->dir_x;
	cub->player->dir_x = cub->player->dir_x * cos(rotation_speed) - cub->player->dir_y
		* sin(rotation_speed);
	cub->player->dir_y = new_dir_x * sin(rotation_speed) + cub->player->dir_y
		* cos(rotation_speed);
	new_plane_x = cub->player->plane_x;
	cub->player->plane_x = cub->player->plane_x * cos(rotation_speed)
		- cub->player->plane_y * sin(rotation_speed);
	cub->player->plane_y = new_plane_x * sin(rotation_speed) + cub->player->plane_y
		* cos(rotation_speed);
}
