/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_player_pos.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: habouda <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 17:22:49 by habouda           #+#    #+#             */
/*   Updated: 2025/04/09 18:11:49 by habouda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	find_player_in_map(t_cub *cub, int *i, int *j)
{
	int	found;

	*i = 0;
	found = 0;
	while (cub->map->map[*i])
	{
		*j = 0;
		while (cub->map->map[*i][*j])
		{
			if (cub->map->map[*i][*j] && cub->map->map[*i][*j] >= '2'
				&& cub->map->map[*i][*j] <= '5')
			{
				found = 1;
				break ;
			}
			(*j)++;
		}
		if (found == 1)
			break ;
		(*i)++;
	}
}

void	apply_player_pos(t_cub *cub, int i, int j)
{
	if (cub->map->map[i][j] == '2')
	{
		cub->player->dir_x = 0;
		cub->player->dir_y = -1;
	}
	else if (cub->map->map[i][j] == '3')
	{
		cub->player->dir_x = -1;
		cub->player->dir_y = 0;
	}
	else if (cub->map->map[i][j] == '4')
	{
		cub->player->dir_x = 1;
		cub->player->dir_y = 0;
	}
	else if (cub->map->map[i][j] == '5')
	{
		cub->player->dir_x = 0;
		cub->player->dir_y = 1;
	}
}

void	get_player_pos(t_cub *cub)
{
	int	i;
	int	j;

	find_player_in_map(cub, &i, &j);
	cub->player = malloc(sizeof(t_player) * 1);
	cub->player->pos_x = (double)j + 0.5;
	cub->player->pos_y = (double)i + 0.5;
	apply_player_pos(cub, i, j);
}
