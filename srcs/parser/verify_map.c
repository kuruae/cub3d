/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verify_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: habouda <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 17:59:00 by emagnani          #+#    #+#             */
/*   Updated: 2025/04/08 19:13:34 by habouda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	get_map_height(char **map)
{
	int	i;

	i = 0;
	while (map[i])
	{
		i++;
	}
	return (i);
}

int	get_map_width(char **map, int height)
{
	int	i;
	int	j;
	int	width;

	i = 0;
	width = 0;
	while (i < height)
	{
		j = 0;
		while (map[i][j])
			j++;
		if (j > width)
			width = j;
		i++;
	}
	return (width);
}

int	check_for_X(char **map)
{
	int i;

	i = 0;
	while (map[i])
	{
		if (map[i][0] == 'X')
			return (1);
		i++;
	}
	return (0);
}