/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_map_closed.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: habouda <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 19:57:38 by habouda           #+#    #+#             */
/*   Updated: 2025/03/28 21:03:02 by habouda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_for_6(t_map *map, int i, int j, int width)
{
	if (j == 0)
	{
		if (map->map[i][j] == 6 && (map->map[i][j + 1] == 0))
			return (1);
	}
	else if (j == width - 1)
	{
		if (map->map[i][j] == 6 && (map->map[i][j - 1] == 0))
			return (1);
	}
	else
	{
		if (map->map[i][j] == 6 && (map->map[i][j - 1] == 0 || map->map[i][j
				+ 1] == 0))
			return (1);
	}
	return (0);
}

int	*is_map_closed_upper(t_map *map, int width)
{
	int	i;
	int	j;
	int	*up;

	up = malloc(sizeof(int) * (width + 1));
	if (!up)
		return (NULL);
	j = 0;
	while (j < width)
	{
		i = 0;
		while (map->map[i] && (j >= ft_tablen(map->map[i])
				|| map->map[i][j] == 6 || map->map[i][j] == -1))
		{
			if (check_for_6(map, i, j, width) == 1)
				return (NULL);
			i++;
		}
		if (map->map[i])
			up[j] = map->map[i][j];
		j++;
	}
	up[j] = -1;
	return (up);
}

int	*is_map_closed_bottom(t_map *map, int height, int width)
{
	int	i;
	int	j;
	int	*bottom;

	bottom = malloc(sizeof(int) * (width + 1));
	if (!bottom)
		return (NULL);
	j = 0;
	while (j < width)
	{
		i = height - 1;
		while (map->map[i] && (j >= ft_tablen(map->map[i])
				|| map->map[i][j] == 6 || map->map[i][j] == -1))
		{
			if (check_for_6(map, i, j, width) == 1)
				return (NULL);
			i--;
		}
		if (i >= 0)
			bottom[j] = map->map[i][j];
		j++;
	}
	bottom[j] = -1;
	return (bottom);
}

int	is_map_closed(t_map *map, int height, int width)
{
	int	*up;
	int	*bottom;
	int	i;

	i = 0;
	up = is_map_closed_upper(map, width);
	bottom = is_map_closed_bottom(map, height, width);
	if (!up || !bottom)
	{
		printf("hole in map\n");
		return (0);
	}
	while(up[i] != -1)
	{
		if (up[i] == 0)
		{
			printf("hole in top part of map\n");
			return (0);
		}
		i++;
	}
	while(bottom[i] != -1)
	{
		if (bottom[i] == 0)
		{
			printf("hole in bottom part of map\n");
			return (0);
		}
		i++;
	}
	return (0);
}
