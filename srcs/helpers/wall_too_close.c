/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_too_close.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: habouda <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 16:58:05 by kuru              #+#    #+#             */
/*   Updated: 2025/04/08 17:44:17 by habouda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static const double	g_wall_buffer = 0.3;

static double	get_wall_distance_x(double x, int map_x)
{
	if (x < map_x)
		return (map_x - x);
	else if (x > map_x + 1)
		return (x - (map_x + 1));
	return (0);
}

static double	get_wall_distance_y(double y, int map_y)
{
	if (y < map_y)
		return (map_y - y);
	else if (y > map_y + 1)
		return (y - (map_y + 1));
	return (0);
}

/**
 * @brief Checks if a wall is too close to the player in a specific cell
 *
 * Checks a specific cell relative to the player's position
 * to determine if it contains a wall that is too close to the player.
 * It calculates the distance between the player and the wall in both X and Y
 * directions, and checks if either distance is less than a predefined buffer.
 *
 * @param cub		Pointer to the main cub struct
 * @param x			The x coordinate
 * @param y			The y coordinate
 * @param coords  	Array containing [y_offset, x_offset]
 *
 * @return 1 if a wall in the current cell is too close, else 0
 */
static int	check_wall_cell(t_cub *cub, double x, double y, int *coords)
{
	double	dist_x;
	double	dist_y;
	int		map_y;
	int		map_x;

	map_y = (int)y + coords[0];
	map_x = (int)x + coords[1];
	if (map_y < 0 || map_x < 0 || map_y >= get_map_height(cub->map->map)
		|| (size_t)map_x >= ft_strlen(cub->map->map[map_y]))
		return (0);
	if (cub->map->map[map_y][map_x] == '1')
	{
		dist_x = get_wall_distance_x(x, map_x);
		dist_y = get_wall_distance_y(y, map_y);
		if (dist_x < g_wall_buffer && dist_y < g_wall_buffer)
			return (1);
	}
	return (0);
}

/**
 * @brief Checks if a point is close to any wall in the map
 *
 * Scans a 3x3 grid around (x, y)
 * to determine if there is a wall nearby. It checks each cell
 * in the grid by calling check_wall_cell() for each position.
 *
 * @param cub	Pointer to the main cub struct
 * @param x		The x coordinate
 * @param y		The y coordinate
 *
 * @return 1 if there is a wall close to the given, else 0
 */
int	is_close_to_wall(t_cub *cub, double x, double y)
{
	int	coords[2];
	int	i;
	int	j;

	i = -2;
	while (++i <= 1)
	{
		j = -2;
		while (++j <= 1)
		{
			coords[0] = i;
			coords[1] = j;
			if (check_wall_cell(cub, x, y, coords))
				return (1);
		}
	}
	return (0);
}
