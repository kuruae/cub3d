/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kuru <kuru@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 18:50:01 by habouda           #+#    #+#             */
/*   Updated: 2025/04/08 22:21:30 by kuru             ###   ########.fr       */
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

static void select_texture_dimensions(t_cub *cub, int *width, int *height)
{
    if (cub->ray->side == 1)
    {
        if (cub->ray->step_y < 0)
        {
            *width = cub->no_size->width;
            *height = cub->no_size->height;
        }
        else
        {
            *width = cub->so_size->width;
            *height = cub->so_size->height;
        }
    }
    else
    {
        if (cub->ray->step_x > 0)
        {
            *width = cub->ea_size->width;
            *height = cub->ea_size->height;
        }
        else
        {
            *width = cub->we_size->width;
            *height = cub->we_size->height;
        }
    }
}

void draw_wall(t_cub *cub, int x)
{
	int y_axis;
	int texture_x;
	int texture_y;
	int color;
	int texture_width;
	int texture_height;

	select_texture_dimensions(cub, &texture_width, &texture_height);	
	// Calculate texture_x with bounds checking
	texture_x = (int)(cub->ray->wall_x * texture_width) % texture_width;
	if (texture_x < 0) texture_x += texture_width;
	
	y_axis = cub->ray->draw_start;
	while (y_axis < cub->ray->draw_end)
	{
		// Calculate texture_y with bounds checking
		texture_y = (int)((y_axis - cub->ray->draw_start) * texture_height / cub->ray->line_height);
		if (texture_y < 0) 
			texture_y = 0;
		if (texture_y >= texture_height)
			texture_y = texture_height - 1;
		// Calculate offset using texture width and height
		int offset = (texture_y * texture_width + texture_x) * cub->img->bpp / 8;
		// Access the texture data based on the side of the wall
		if (cub->ray->side == 1) 
		{ // Horizontal walls (North/South)
			if (cub->ray->step_y < 0) // Facing North
				color = *(unsigned int *)(cub->img->north + offset);
			else // Facing South
				color = *(unsigned int *)(cub->img->south + offset);
		}
		else 
		{ // Vertical walls (East/West)
			if (cub->ray->step_x > 0) // Facing East
				color = *(unsigned int *)(cub->img->east + offset);
			else // Facing West
				color = *(unsigned int *)(cub->img->west + offset);
		}
		// Draw the pixel on the screen (check bounds)
		if (y_axis >= 0 && y_axis < HEIGHT && x >= 0 && x < WIDTH)
			*(unsigned int *)(cub->img->adrr + (y_axis * cub->img->line_length + x * cub->img->bpp / 8)) = color;
		y_axis++;
	}
}
