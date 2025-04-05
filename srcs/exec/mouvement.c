/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouvement.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kuru <kuru@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 16:43:42 by kuru              #+#    #+#             */
/*   Updated: 2025/04/05 17:08:55 by kuru             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	move_forward(t_cub *cub)
{
	double	new_x;
	double	new_y;
	
	new_x = cub->player->pos_x + cub->player->dir_x * MOVE_SPEED;
	new_y = cub->player->pos_y + cub->player->dir_y * MOVE_SPEED;
	if (cub->map->map[(int)cub->player->pos_y][(int)new_x] != '1')
	{
		if (!is_close_to_wall(cub, new_x, cub->player->pos_y))
			cub->player->pos_x = new_x;
	}
	if (cub->map->map[(int)new_y][(int)cub->player->pos_x] != '1')
	{
		if (!is_close_to_wall(cub, cub->player->pos_x, new_y))
			cub->player->pos_y = new_y;
	}
}

void	move_backwards(t_cub *cub)
{
	double	new_x;
	double	new_y;
	
	new_x = cub->player->pos_x - cub->player->dir_x * MOVE_SPEED;
	new_y = cub->player->pos_y - cub->player->dir_y * MOVE_SPEED;
	
	if (cub->map->map[(int)cub->player->pos_y][(int)new_x] != '1')
	{
		if (!is_close_to_wall(cub, new_x, cub->player->pos_y))
			cub->player->pos_x = new_x;
	}
	if (cub->map->map[(int)new_y][(int)cub->player->pos_x] != '1')
	{
		if (!is_close_to_wall(cub, cub->player->pos_x, new_y))
			cub->player->pos_y = new_y;
	}
}

void	move_left(t_cub *cub)
{
	double	new_x;
	double	new_y;
	
	new_x = cub->player->pos_x + cub->player->dir_y * MOVE_SPEED;
	new_y = cub->player->pos_y - cub->player->dir_x * MOVE_SPEED;
	
	if (cub->map->map[(int)cub->player->pos_y][(int)new_x] != '1')
	{
		if (!is_close_to_wall(cub, new_x, cub->player->pos_y))
			cub->player->pos_x = new_x;
	}
	if (cub->map->map[(int)new_y][(int)cub->player->pos_x] != '1')
	{
		if (!is_close_to_wall(cub, cub->player->pos_x, new_y))
			cub->player->pos_y = new_y;
	}
}

void	move_right(t_cub *cub)
{
	double	new_x;
	double	new_y;
	
	new_x = cub->player->pos_x - cub->player->dir_y * MOVE_SPEED;
	new_y = cub->player->pos_y + cub->player->dir_x * MOVE_SPEED;
	
	if (cub->map->map[(int)cub->player->pos_y][(int)new_x] != '1')
	{
		if (!is_close_to_wall(cub, new_x, cub->player->pos_y))
			cub->player->pos_x = new_x;
	}
	if (cub->map->map[(int)new_y][(int)cub->player->pos_x] != '1')
	{
		if (!is_close_to_wall(cub, cub->player->pos_x, new_y))
			cub->player->pos_y = new_y;
	}
}

int	mouvement(int keysim, t_cub *cub)
{
	if (keysim == XK_w)
		move_forward(cub);
	if (keysim == XK_s)
		move_backwards(cub);
	if (keysim == XK_a)
		move_left(cub);
	if (keysim == XK_d)
		move_right(cub);
	if (keysim == XK_Left)
		rotate_left(cub, ROTATE_SPEED);
	if (keysim == XK_Right)
		rotate_right(cub, ROTATE_SPEED);
	return (0);
}