/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_map_closed.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: habouda <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 19:57:38 by habouda           #+#    #+#             */
/*   Updated: 2025/03/28 20:10:20 by habouda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
			i++;
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
			i--;
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
	printf("upper line is \n");
	while (up[i] != -1)
	{
		printf(" %d", up[i]);
		i++;
	}
	printf("\n");
	i = 0;
	printf("bottom line is \n");
	while (bottom[i] != -1)
	{
		printf(" %d", bottom[i]);
		i++;
	}
	printf("\n");
	return (0);
}
