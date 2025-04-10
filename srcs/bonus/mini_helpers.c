/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_helpers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: habouda <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 19:48:58 by habouda           #+#    #+#             */
/*   Updated: 2025/04/10 19:49:28 by habouda          ###   ########.fr       */
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