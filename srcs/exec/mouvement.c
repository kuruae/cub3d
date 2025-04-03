/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouvement.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: habouda <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 01:58:03 by habouda           #+#    #+#             */
/*   Updated: 2025/04/03 02:19:56 by habouda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	move_forward(t_cub *cub)
{
	double	n_x;
	double	n_y;
	int		row_length;

	n_x = cub->player->pos_x;
	n_y = cub->player->pos_y;
	if (cub->map->map[(int)cub->player->pos_y] [(int)(cub->player->pos_x + cub->player->dir_x * MOVE_SPEED)] != '1')
		n_x = cub->player->pos_x + cub->player->dir_x * MOVE_SPEED;
	if (cub->map->map[(int)(cub->player->pos_y + cub->player->dir_y * MOVE_SPEED)][(int)cub->player->pos_x] != '1')
		n_y = cub->player->pos_y + cub->player->dir_y * MOVE_SPEED;
	if (n_y >= 0)
	{
		row_length = ft_strlen(cub->map->map[(int)n_y]);
		if (n_x >= 0 && n_x < row_length)
		{
			if (cub->map->map[(int)n_y][(int)n_x] != '1')
			{
				cub->player->pos_x = n_x;
				cub->player->pos_y = n_y;
			}
		}
	}
}
void	move_backwards(t_cub *cub)
{
	double	n_x;
	double	n_y;
	int		row_length;

	n_x = cub->player->pos_x;
	n_y = cub->player->pos_y;
	if (cub->map->map[(int)cub->player->pos_y]
		[(int)(cub->player->pos_x - cub->player->dir_x * MOVE_SPEED)] != '1')
		n_x = cub->player->pos_x - cub->player->dir_x * MOVE_SPEED;
	if (cub->map->map[(int)(cub->player->pos_y - cub->player->dir_y * MOVE_SPEED)]
		[(int)cub->player->pos_x] != '1')
		n_y = cub->player->pos_y - cub->player->dir_y * MOVE_SPEED;
	if (n_y >= 0)
	{
		row_length = ft_strlen(cub->map->map[(int)n_y]);
		if (n_x >= 0 && n_x < row_length)
		{
			if (cub->map->map[(int)n_y][(int)n_x] != '1')
			{
				cub->player->pos_x = n_x;
				cub->player->pos_y = n_y;
			}
		}
	}
}


void	move_left(t_cub *cub)
{
	double	n_x;
	double	n_y;
	int		row_length;

	n_x = cub->player->pos_x;
	n_y = cub->player->pos_y;
	if (cub->map->map[(int)cub->player->pos_y] [(int)(cub->player->pos_x + cub->player->dir_y * MOVE_SPEED)] != '1')
		n_x = cub->player->pos_x + cub->player->dir_y * MOVE_SPEED;
	if (cub->map->map[(int)(cub->player->pos_y - cub->player->dir_x * MOVE_SPEED)][(int)cub->player->pos_x] != '1')
		n_y = cub->player->pos_y - cub->player->dir_x * MOVE_SPEED;
	if (n_y >= 0)
	{
		row_length = ft_strlen(cub->map->map[(int)n_y]);
		if (n_x >= 0 && n_x < row_length)
		{
			if (cub->map->map[(int)n_y][(int)n_x] != '1')
			{
				cub->player->pos_x = n_x;
				cub->player->pos_y = n_y;
			}
		}
	}
}

void	move_right(t_cub *cub)
{
	double	n_x;
	double	n_y;
	int		row_length;

	n_x = cub->player->pos_x;
	n_y = cub->player->pos_y;
	if (cub->map->map[(int)cub->player->pos_y] [(int)(cub->player->pos_x - cub->player->dir_y * MOVE_SPEED)] != '1')
		n_x = cub->player->pos_x - cub->player->dir_y * MOVE_SPEED;
	if (cub->map->map[(int)(cub->player->pos_y + cub->player->dir_x * MOVE_SPEED)][(int)cub->player->pos_x] != '1')
		n_y = cub->player->pos_y + cub->player->dir_x * MOVE_SPEED;
	if (n_y >= 0)
	{
		row_length = ft_strlen(cub->map->map[(int)n_y]);
		if (n_x >= 0 && n_x < row_length)
		{
			if (cub->map->map[(int)n_y][(int)n_x] != '1')
			{
				cub->player->pos_x = n_x;
				cub->player->pos_y = n_y;
			}
		}
	}
}



int mouvement(int keysim, t_cub *cub)
{
	if (keysim == XK_w)
		move_forward(cub);
	if (keysim == XK_s)
		move_backwards(cub);
	if (keysim == XK_a)
		move_left(cub);
	if (keysim == XK_d)
		move_right(cub);
	return 0;
}