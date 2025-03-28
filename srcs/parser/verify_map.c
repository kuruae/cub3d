/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verify_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emagnani <emagnani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 17:59:00 by emagnani          #+#    #+#             */
/*   Updated: 2025/03/28 18:47:33 by emagnani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	get_map_height(int **map)
{
	int	i;

	i = 0;
	while (map[i])
	{
		i++;
	}
	return (i);
}

int get_map_width(int **map, int height)
{
	int i;
	int	j;
	int	width;

	i = 0;
	width = 0;
	while(i < height)
	{
		j = 0;
		while(map[i][j] != -1)
			j++;
		if (j > width)
			width = j;
		i++;
	}
	return (width);
}

