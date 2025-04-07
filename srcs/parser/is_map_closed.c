	/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_map_closed.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: habouda <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 19:57:38 by habouda           #+#    #+#             */
/*   Updated: 2025/04/07 16:18:35 by habouda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_for_6(char **map, int i, int j, int width)
{
	if (j == 0)
	{
		if (map[i][j] == '1' && (map[i][j + 1] == '0'))
			return (1);
	}
	else if (j == width - 1)
	{
		if (map[i][j] == '1' && (map[i][j - 1] == '0'))
			return (1);
	}
	else
	{
		if (map[i][j] == '1' && (map[i][j - 1] == '0' || map[i][j + 1] == '0'))
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

int validate_array(char **arr, int size)
{
    int i;
    int j;
    int prev_len;
    int curr_len;

    if (size <= 1)
        return (0);  // No comparison needed with 0 or 1 lines
    for (i = 1; i < size; i++)
    {
        // Get lengths of current and previous lines
        prev_len = 0;
        curr_len = 0;
        while (arr[i - 1][prev_len] != '\0')
            prev_len++;
        while (arr[i][curr_len] != '\0')
            curr_len++;

        // Check if current line is longer than previous line
        if (curr_len > prev_len)
        {
            // Check for '0' in positions where previous line ends
            for (j = prev_len; j < curr_len; j++)
            {
                if (arr[i][j] == '0')
                {
                    // Found a '0' in the extended part
                    return (1);  // Error condition met
                }
            }
        }
    }
    return (0);  // No errors found
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
	int i = 0;

	up = is_map_closed_upper(map->map, width);
	bottom = is_map_closed_bottom(map->map, height, width);
	printf("\n");
	printf("up: %s\n", up);
	printf("bottom: %s\n", bottom);
	printf("\n");
	while (map->map[i])
	{
		printf("OROGINLE :%s\n", map->map[i]);
		i++;
	}
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
		printf("errors valdiate claude david\n");
	}
	return (0);
}
