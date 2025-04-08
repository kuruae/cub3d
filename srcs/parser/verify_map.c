/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verify_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: habouda <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 17:59:00 by emagnani          #+#    #+#             */
/*   Updated: 2025/04/08 20:11:00 by habouda          ###   ########.fr       */
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

int	check_for_x(char **map)
{
	int	i;

	i = 0;
	while (map[i])
	{
		if (map[i][0] == 'X')
			return (1);
		i++;
	}
	return (0);
}

char	*is_map_closed_upper(char **map, size_t width)
{
	size_t	i;
	size_t	j;
	char	*up;

	up = malloc(sizeof(char) * (width + 1));
	if (!up)
		return (NULL);
	j = 0;
	while (j < width)
	{
		i = 0;
		while (map[i] && (j >= ft_strlen(map[i])))
		{
			i++;
		}
		if (map[i])
			up[j] = map[i][j];
		j++;
	}
	up[j] = '\0';
	return (up);
}

char	*is_map_closed_bottom(char **map, int height, size_t width)
{
	size_t	i;
	size_t	j;
	char	*bottom;

	bottom = malloc(sizeof(char) * (width + 1));
	if (!bottom)
		return (NULL);
	j = 0;
	while (j < width)
	{
		i = height - 1;
		while (map[i] && (j >= ft_strlen(map[i])))
		{
			i--;
		}
		if (i >= 0)
			bottom[j] = map[i][j];
		j++;
	}
	bottom[j] = '\0';
	return (bottom);
}
