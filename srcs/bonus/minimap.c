/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: habouda <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 18:28:50 by habouda           #+#    #+#             */
/*   Updated: 2025/04/10 19:49:26 by habouda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_mini_walls(t_map *map, t_minimap *mini)
{
	int x;
	int y;
	
	y = 0;
	while(map->map[y] && y < mini->map_height)
	{
		x = 0;	
		while (x < mini->map_width)
		{
			if (x <= (int)ft_strlen(map->map[y]) && map->map[y][x] == '1')
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
	t_minimap *mini;

	mini = cub->mini;
	draw_square(mini);
	draw_mini_walls(map, mini);
	draw_mini_player(cub, map, mini);
	mlx_put_image_to_window(cub->mlx, cub->mlx_win, mini->img, 20, 20);
}
