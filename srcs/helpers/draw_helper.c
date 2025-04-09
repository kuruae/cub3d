/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_helper.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: habouda <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 17:51:19 by habouda           #+#    #+#             */
/*   Updated: 2025/04/09 17:52:20 by habouda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	select_east_west_texture_dimensions(t_cub *cub, int *width, int *height,
	char **texture_data)
{
	if (cub->ray->dir_x > 0)
	{
		*width = cub->we_size->width;
		*height = cub->we_size->height;
		*texture_data = cub->img->west;
	}
	else
	{
		*width = cub->ea_size->width;
		*height = cub->ea_size->height;
		*texture_data = cub->img->east;
	}
}

void	select_north_south_texture_dimensions(t_cub *cub, int *width, int *height,
	char **texture_data)
{
	if (cub->ray->dir_y > 0)
	{
		*width = cub->so_size->width;
		*height = cub->so_size->height;
		*texture_data = cub->img->south;
	}
	else
	{
		*width = cub->no_size->width;
		*height = cub->no_size->height;
		*texture_data = cub->img->north;
	}
}