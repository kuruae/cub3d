/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_map_closed.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: habouda <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 19:57:38 by habouda           #+#    #+#             */
/*   Updated: 2025/03/31 18:44:44 by habouda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_for_6(char **map, int i, int j, int width)
{
	if (j == 0)
	{
		if (map[i][j] == VOID && (map[i][j + 1] == '0'))
			return (1);
	}
	else if (j == width - 1)
	{
		if (map[i][j] == VOID && (map[i][j - 1] == '0'))
			return (1);
	}
	else
	{
		if (map[i][j] == VOID && (map[i][j - 1] == '0' || map[i][j + 1] == '0'))
			return (1);
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
		while (map[i] && (j >= ft_strlen(map[i]) || map[i][j] == VOID))
		{
			if (check_for_6(map, i, j, width) == 1)
				return (NULL);
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
		while (map[i] && (j >= ft_strlen(map[i]) || map[i][j] == VOID))
		{
			if (check_for_6(map, i, j, width) == 1)
				return (NULL);
			i--;
		}
		if (i >= 0)
			bottom[j] = map[i][j];
		j++;
	}
	bottom[j] = '\0';
	return (bottom);
}

int	check_zero(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '0')
			return (1);
		i++;
	}
	return (0);
}

int	is_map_closed(t_map *map, int height, int width)
{
	char	*up;
	char	*bottom;
	char	**rotated;

	up = is_map_closed_upper(map->map, width);
	bottom = is_map_closed_bottom(map->map, height, width);
	if (!up || !bottom || check_zero(up) || check_zero(bottom))
	{
		if (up)
			free(up);
		if (bottom)
			free(bottom);
		return (1);
	}
	free(up);
	free(bottom);
	rotated = rotate_array(map->map);
	up = is_map_closed_upper(rotated, height);
	bottom = is_map_closed_bottom(rotated, width, height);
	if (!up || !bottom || check_zero(up) || check_zero(bottom))
	{
		if (up)
			free(up);
		if (bottom)
			free(bottom);
		return (1);
	}
	ft_free_str_array(&rotated);
	return (0);
}
