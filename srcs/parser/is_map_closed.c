/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_map_closed.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: habouda <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 19:57:38 by habouda           #+#    #+#             */
/*   Updated: 2025/04/08 17:45:06 by habouda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

int	validate_array(char **arr, int size)
{
	int	i;
	int	j;
	int	prev_len;
	int	curr_len;

	i = 0;
	while (++i < size)
	{
		prev_len = 0;
		curr_len = 0;
		while (arr[i - 1][prev_len] != '\0')
			prev_len++;
		while (arr[i][curr_len] != '\0')
			curr_len++;
		if (curr_len > prev_len)
		{
			j = prev_len - 1;
			while (++j < curr_len)
			{
				if (arr[i][j] == '0')
					return (1);
			}
		}
	}
	return (0);
}

int	check_zero(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '0' || (str[i] >= '2' && str[i] <= '5'))
			return (1);
		i++;
	}
	return (0);
}

int	is_map_closed(t_map *map, int height, int width)
{
	char	*up;
	char	*bottom;

	up = is_map_closed_upper(map->map, width);
	bottom = is_map_closed_bottom(map->map, height, width);
	printf("\n");
	printf("up: %s\n", up);
	printf("bottom: %s\n", bottom);
	printf("\n");
	if (!up || !bottom || check_zero(up) || check_zero(bottom))
	{
		if (up)
			free(up);
		if (bottom)
			free(bottom);
		return (1);
	}
	if (validate_array(map->map, height) == 1)
	{
		printf("Map Opended on the sides\n");
		return (1);
	}
	return (0);
}
