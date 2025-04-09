/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emagnani <emagnani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 18:50:01 by habouda           #+#    #+#             */
/*   Updated: 2025/04/09 17:07:46 by emagnani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_floor_ceiling(t_cub *cub)
{
	int	x;
	int	y;
	int	color;

	color = rgb_to_int(cub->map->ceiling_color);
	y = -1;
	while (++y < HEIGHT / 2)
	{
		x = -1;
		while (++x < WIDTH)
		{
			*(unsigned int *)(cub->img->adrr + (y * cub->img->line_length + x * (cub->img->bpp / 8))) = color;
		}
	}
	color = rgb_to_int(cub->map->floor_color);
	y = (HEIGHT / 2) -1;
	while (++y < HEIGHT)
	{
		x = -1;
		while (++x < WIDTH)
		{
			*(unsigned int *)(cub->img->adrr + (y * cub->img->line_length + x * (cub->img->bpp / 8))) = color;
		}
	}
}

static void select_texture_dimensions(t_cub *cub, int *width, int *height, char **texture_data)
{
	if (cub->ray->side == 0)
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
	else
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
}

void static	draw_loop(t_cub *cub, t_draw_wall draw, int x)
{
	while (draw.y_axis < cub->ray->draw_end)
	{
		draw.texture_y = (int)draw.tex_pos & (draw.texture_height - 1);
		draw.tex_pos += draw.step;
		draw.offset = (draw.texture_y * draw.texture_width + draw.texture_x) * cub->img->bpp / 8;
		draw.texture_y = *(unsigned int *)(draw.texture_data + draw.offset);
		if (draw.y_axis >= 0 && draw.y_axis < HEIGHT && x >= 0 && x < WIDTH)
			*(unsigned int *)(cub->img->adrr + (draw.y_axis
						* cub->img->line_length + x * cub->img->bpp / 8)) = draw.texture_y;
		draw.y_axis++;
	}
}

void draw_wall(t_cub *cub, int x)
{
	t_draw_wall draw;

	select_texture_dimensions(cub, &draw.texture_width, &draw.texture_height, &draw.texture_data);
	if (cub->ray->side == 0)
		draw.wall_x = cub->player->pos_y + cub->ray->wall_dist * cub->ray->dir_y;
	else
		draw.wall_x = cub->player->pos_x + cub->ray->wall_dist * cub->ray->dir_x;
	draw.wall_x -= floor(draw.wall_x);
	draw.texture_x = (int)(draw.wall_x * draw.texture_width);
	if (draw.texture_x < 0)
		draw.texture_x = 0;
	if (draw.texture_x >= draw.texture_width)
		draw.texture_x = draw.texture_width - 1;
	draw.step = (double)draw.texture_height / cub->ray->line_height;
	draw.tex_pos = (cub->ray->draw_start - HEIGHT / 2 + cub->ray->line_height / 2) * draw.step;
	draw.y_axis = cub->ray->draw_start;
	draw_loop(cub, draw, x);
}
