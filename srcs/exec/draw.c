/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kuru <kuru@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 18:50:01 by habouda           #+#    #+#             */
/*   Updated: 2025/04/10 23:29:19 by kuru             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_floor_ceiling(t_cub *cub, int color)
{
	int	x;
	int	y;

	y = -1;
	while (++y < HEIGHT / 2)
	{
		x = -1;
		while (++x < WIDTH)
		{
			*(unsigned int *)(cub->img->adrr + (y * cub->img->line_length + x
						* (cub->img->bpp / 8))) = color;
		}
	}
	color = rgb_to_int(cub->map->floor_color);
	y = (HEIGHT / 2) - 1;
	while (++y < HEIGHT)
	{
		x = -1;
		while (++x < WIDTH)
		{
			*(unsigned int *)(cub->img->adrr + (y * cub->img->line_length + x
						* (cub->img->bpp / 8))) = color;
		}
	}
}

static void	select_texture_dimension(t_cub *cub, int *width, int *height,
		char **texture_data)
{
	if (cub->ray->side == 0)
		select_east_west_texture_dimensions(cub, width, height, texture_data);
	else
		select_north_south_texture_dimensions(cub, width, height, texture_data);
}

static int	add_depth(t_draw_wall draw, double depth_factor)
{
	t_rgb			rgb;

	rgb.r = (draw.texture_y >> 16) & 0xFF;
	rgb.g = (draw.texture_y >> 8) & 0xFF;
	rgb.b = draw.texture_y & 0xFF;
	rgb.r = (int)(rgb.r * depth_factor);
	rgb.g = (int)(rgb.g * depth_factor);
	rgb.b = (int)(rgb.b * depth_factor);
	return (rgb_to_int(rgb));
}

/**
 * @brief Draws a vertical column of pixels for a wall
 * 
 * iterates through the pixels of a wall slice and applies
 * the right texture with a depth effect (making distant walls darker)
 * before drawing to the screen buffer.
 *
 * @param cub Main game structure
 * @param draw Structure holding texture and drawing coordinates
 * @param x X-coordinate on the screen where this wall slice is being drawn
 * 
 * 
 * @details DEPTH/FOG EFFECT EXPLANATION pour toi hugo
 * ---------------------------
 * The depth creates a fog-like darkening of walls as they get further away.
 * This helps create depth perception in the rendering.
 * 
 * How it works:
 * @
 * 1. First you have to calculate the depth factor
 *    which the fomula that can be popularized as:
 *    - CLOSE WALLS BRIGHTNESS - fmin(MAX DARKNESS, wall_dist / MAX DIST)
 *    in our codebase: (1.0 - fmin(0.8, cub->ray->wall_dist / 12.0))
 *      - CLOSE WALLS BRIGHTNESS = 1.0 (100% brightness)
 *   	- MAX DARKNESS = 0.8 (80% darkness)
 *		- MAX DIST = 12.0 (12 units)
 *   
 * 	  So:
 *    - wall_dist is the distance to the wall
 *    - The factor decreases as distance increases
 *    - And in our current codebase the maximum 
 * 			darkness is 80% (0.8) at 12.0 units away
 *    - Closer walls stay brighter (factor closer to 1.0)
 * 
 * 2. Color Modification (in add_depth):
 *    - RGB values of the texture are extracted using bitwise operations:
 *      > Red:   (color >> 16) & 0xFF
 *      > Green: (color >> 8) & 0xFF
 *      > Blue:  color & 0xFF
 *    - Each component is then darkened proportionally to the distance
 *    - The darker color is reconstructed using rgb_to_int
 * 
 * Visual Effect:
 * - Walls right in front of player are shown at full brightness
 * - Walls get progressively darker as they get further away
 * - Maximum darkness is capped at 20% of original brightness
 * 
 * Example:
 * - Wall at 0 units:   depth_factor = 1.0   (100% brightness)
 * - Wall at 6 units:   depth_factor = 0.6   (60% brightness)
 * - Wall at 12+ units: depth_factor = 0.2   (20% brightness)
 */
void static	draw_loop(t_cub *cub, t_draw_wall draw, int x)
{
	double			depht_factor;
	unsigned int	depth_y;

	depht_factor = 1.0 - fmin(0.8, cub->ray->wall_dist / 12.0);
	while (draw.y_axis < cub->ray->draw_end)
	{
		draw.texture_y = (int)draw.tex_pos & (draw.texture_height - 1);
		draw.tex_pos += draw.step;
		draw.offset = (draw.texture_y * draw.texture_width + draw.texture_x)
			* cub->img->bpp / 8;
		draw.texture_y = *(unsigned int *)(draw.texture_data + draw.offset);
		depth_y = add_depth(draw, depht_factor);
		if (draw.y_axis >= 0 && draw.y_axis < HEIGHT && x >= 0 && x < WIDTH)
			*(unsigned int *)(cub->img->adrr + (draw.y_axis
						* cub->img->line_length + x * cub->img->bpp
						/ 8)) = depth_y;
		draw.y_axis++;
	}
}

void	draw_wall(t_cub *cub, int x)
{
	t_draw_wall	draw;

	select_texture_dimension(cub, &draw.texture_width, &draw.texture_height,
		&draw.texture_data);
	if (cub->ray->side == 0)
		draw.wall_x = cub->player->pos_y + cub->ray->wall_dist
			* cub->ray->dir_y;
	else
		draw.wall_x = cub->player->pos_x + cub->ray->wall_dist
			* cub->ray->dir_x;
	draw.wall_x -= floor(draw.wall_x);
	draw.texture_x = (int)(draw.wall_x * draw.texture_width);
	if (draw.texture_x < 0)
		draw.texture_x = 0;
	if (draw.texture_x >= draw.texture_width)
		draw.texture_x = draw.texture_width - 1;
	draw.step = (double)draw.texture_height / cub->ray->line_height;
	draw.tex_pos = (cub->ray->draw_start - HEIGHT / 2 + cub->ray->line_height
			/ 2) * draw.step;
	draw.y_axis = cub->ray->draw_start;
	draw_loop(cub, draw, x);
}
