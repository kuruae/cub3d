/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_map_closed.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: habouda <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 19:57:38 by habouda           #+#    #+#             */
/*   Updated: 2025/04/09 18:22:30 by habouda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_extended_zeros(char *line, int start, int end)
{
	int	i;

	i = start;
	while (i < end)
	{
		if (line[i] == '0')
			return (1);
		i++;
	}
	return (0);
}

int	compare_lines(char *prev_line, char *curr_line)
{
	int	prev_len;
	int	curr_len;

	prev_len = ft_strlen(prev_line);
	curr_len = ft_strlen(curr_line);
	if (curr_len > prev_len)
	{
		if (check_extended_zeros(curr_line, prev_len, curr_len))
			return (1);
	}
	else if (curr_len < prev_len)
	{
		if (check_extended_zeros(prev_line, curr_len, prev_len))
			return (1);
	}
	return (0);
}

int	validate_array(char **arr, int size)
{
	int	i;

	if (size <= 1)
		return (0);
	i = 1;
	while (i < size)
	{
		if (compare_lines(arr[i - 1], arr[i]))
			return (1);
		i++;
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
	if (validate_array(map->map, height) == 1)
	{
		printf("Map Opended on the sides\n");
		return (1);
	}
	return (0);
}
