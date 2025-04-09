/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: habouda <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 18:45:38 by habouda           #+#    #+#             */
/*   Updated: 2025/04/09 17:37:39 by habouda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	find_x_ray(t_cub *cub)
{
	if (cub->ray->dir_x > 0)
	{
		cub->ray->sidedist_x = (cub->ray->map_x + 1.0 - cub->player->pos_x)
			* cub->ray->deltadist_x;
		cub->ray->step_x = 1;
	}
	else if (cub->ray->dir_x < 0)
	{
		cub->ray->sidedist_x = (cub->player->pos_x - cub->ray->map_x)
			* cub->ray->deltadist_x;
		cub->ray->step_x = -1;
	}
	else
	{
		cub->ray->sidedist_x = INT_MAX;
		cub->ray->step_x = 0;
	}
}

void	find_y_ray(t_cub *cub)
{
	if (cub->ray->dir_y > 0)
	{
		cub->ray->sidedist_y = (cub->ray->map_y + 1.0 - cub->player->pos_y)
			* cub->ray->deltadist_y;
		cub->ray->step_y = 1;
	}
	else if (cub->ray->dir_y < 0)
	{
		cub->ray->sidedist_y = (cub->player->pos_y - cub->ray->map_y)
			* cub->ray->deltadist_y;
		cub->ray->step_y = -1;
	}
	else
	{
		cub->ray->sidedist_y = INT_MAX;
		cub->ray->step_y = 0;
	}
}

void	calculate_ray(t_cub *cub)
{
	cub->ray->map_x = (int)cub->player->pos_x;
	cub->ray->map_y = (int)cub->player->pos_y;
	if (cub->ray->dir_x != 0)
		cub->ray->deltadist_x = fabs(1 / cub->ray->dir_x);
	else
		cub->ray->deltadist_x = 0;
	if (cub->ray->dir_y != 0)
		cub->ray->deltadist_y = fabs(1 / cub->ray->dir_y);
	else
		cub->ray->deltadist_y = 0;
	find_x_ray(cub);
	find_y_ray(cub);
	while (cub->map->map[cub->ray->map_y][cub->ray->map_x] != 49)
		apply_dda(cub);
	if (cub->ray->side == 0)
		cub->ray->wall_dist = (cub->ray->map_x - cub->player->pos_x + (1
					- cub->ray->step_x) / 2) / cub->ray->dir_x;
	else
		cub->ray->wall_dist = (cub->ray->map_y - cub->player->pos_y + (1
					- cub->ray->step_y) / 2) / cub->ray->dir_y;
}

void	apply_dda(t_cub *cub)
{
	if (cub->ray->sidedist_x < cub->ray->sidedist_y)
	{
		cub->ray->sidedist_x += cub->ray->deltadist_x;
		cub->ray->map_x += cub->ray->step_x;
		cub->ray->side = 0;
	}
	else
	{
		cub->ray->sidedist_y += cub->ray->deltadist_y;
		cub->ray->map_y += cub->ray->step_y;
		cub->ray->side = 1;
	}
}

void	wall(t_cub *cub)
{
	cub->ray->line_height = (int)(HEIGHT / cub->ray->wall_dist);
	cub->ray->draw_start = -cub->ray->line_height / 2 + HEIGHT / 2;
	if (cub->ray->draw_start < 0)
		cub->ray->draw_start = 0;
	cub->ray->draw_end = cub->ray->line_height / 2 + HEIGHT / 2;
	if (cub->ray->draw_end >= HEIGHT)
		cub->ray->draw_end = HEIGHT - 1;
	if (cub->ray->side == 0)
		cub->ray->wall_x = cub->player->pos_y + cub->ray->wall_dist
			* cub->ray->dir_y;
	else
		cub->ray->wall_x = cub->player->pos_x + cub->ray->wall_dist
			* cub->ray->dir_x;
	cub->ray->wall_x -= floor(cub->ray->wall_x);
}
