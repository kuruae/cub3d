/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: habouda <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 18:28:50 by habouda           #+#    #+#             */
/*   Updated: 2025/04/10 19:18:08 by habouda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	mini_map_pixel_put(t_minimap *mini, int x, int y, int color)
{
	char *dst;
    
    if (x < 0 || x >= mini->width || y < 0 || y >= mini->height)
        return;
        
    dst = mini->addr + (y * mini->line_length + x * (mini->bits_per_pixel / 8));
    *(unsigned int*)dst = color;
}

void	draw_square(t_minimap *mini)
{
	int y;
	int x;
	
	y = 0;
	while(y < mini->height)
	{
		x = 0;
		while (x < mini->width)
		{
			mini_map_pixel_put(mini, x, y, 0x222222);
			x++;
		}
		y++;
	}
}

void	put_the_walls(t_minimap *mini, int draw_x, int draw_y)
{
	int i;
	int j;

	i = 0;
	while (i < 8)
	{
		j = 0;
		while (j < 8)
		{
			mini_map_pixel_put(mini, draw_x + i, draw_y + j, 0xAAAAAA);
			j++;
		}
		i++;
	}
}

void	draw_mini_walls(t_map *map, t_minimap *mini)
{
	int x;
	int y;
	
	y = 0;
	while(y < mini->map_height)
	{
		x = 0;
		while (x < mini->map_width)
		{
			if (map->map[y][x] == '1')
			{
				put_the_walls(mini, x * 8, y * 8);
			}
			x++;
		}
		y++;
	}
}

void	put_the_player(t_minimap *mini, int draw_x, int draw_y)
{
	int i;
	int j;

	i = 0;
	while (i < 8)
	{
		j = 0;
		while (j < 8)
		{
			mini_map_pixel_put(mini, draw_x + i, draw_y + j, 0xAA0000);
			j++;
		}
		i++;
	}
}

void	draw_mini_player(t_cub *cub, t_map *map, t_minimap *mini)
{
	int x;
	int y;

	y = 0;
	(void)map;
	while(y < mini->map_height)
	{
		x = 0;
		while (x < mini->map_width)
		{
			if (x == (int)cub->player->pos_x && y == (int)cub->player->pos_y)
			{
				put_the_player(mini, x * 8, y * 8);
			}
			x++;
		}
		y++;
	}
}

void	draw_minimap(t_cub *cub, t_map *map)
{
	t_minimap mini;

	mini.map_height = get_map_height(map->map);
	mini.map_width = get_map_width(map->map, mini.map_height);
	mini.height = mini.map_height * 8;
	mini.width = mini.map_width * 8;
	mini.img = mlx_new_image(cub->mlx, mini.width, mini.height);
	if (!mini.img)
        return;
	mini.addr = mlx_get_data_addr(mini.img, &mini.bits_per_pixel, &mini.line_length, &mini.endian);
	draw_square(&mini);
	draw_mini_walls(map, &mini);
	draw_mini_player(cub, map, &mini);
	mlx_put_image_to_window(cub->mlx, cub->mlx_win, mini.img, 20, 20);
}
