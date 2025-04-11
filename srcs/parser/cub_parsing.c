/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kuru <kuru@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 18:21:10 by habouda           #+#    #+#             */
/*   Updated: 2025/04/11 18:01:18 by kuru             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <errno.h>
#include <string.h>

t_err_status	validate_file_path(const char *file, char *msg)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (err_handler(msg, ERR_MAP_PATH));
	close(fd);
	return (SUCCESS);
}

static t_err_status	init_map(t_map *map)
{
	map->map = NULL;
	map->no_texture = NULL;
	map->so_texture = NULL;
	map->we_texture = NULL;
	map->ea_texture = NULL;
	map->floor_color.r = -1;
	map->floor_color.g = -1;
	map->floor_color.b = -1;
	map->ceiling_color.r = -1;
	map->ceiling_color.g = -1;
	map->ceiling_color.b = -1;
	return (SUCCESS);
}

t_err_status	start_parsing_cub_file(char *file, t_map *map)
{
	int	height;
	int	width;

	if (validate_file_path(file, MSG_INVALID_MAP_PATH) != SUCCESS)
		return (ERR_MAP_PATH);
	init_map(map);
	cub_file_readloop(file, map);
	if (map->map == NULL)
		return (ERR_MAP_PATH);
	if (verify_values(map) != SUCCESS)
		return (ERR_VALUES);
	if (verify_data(map) != SUCCESS)
		return (ERR_TEXTURE_PATH);
	height = get_map_height(map->map);
	width = get_map_width(map->map, height);
	if (width < 3 || height < 3)
		return (ERR_VALUES);
	if (is_map_closed(map, height, width))
		return (ERR_INVALID_MAP);
	return (SUCCESS);
}

t_err_status	verify_values(t_map *map)
{
	int	i;
	int	j;
	int	pos;

	pos = 0;
	i = 0;
	while (map->map[i])
	{
		j = 0;
		while (map->map[i][j])
		{
			if (map->map[i][j] >= NORTH && map->map[i][j] <= SOUTH)
				pos++;
			j++;
		}
		i++;
	}
	if (pos != 1)
	{
		ft_putstr_fd("No player or more than one player in map\n", 2);
		return (ERR_POSITION);
	}
	return (SUCCESS);
}

t_err_status	verify_data(t_map *map)
{
	if (!map->no_texture || !map->so_texture || !map->we_texture
		|| !map->ea_texture)
		return (ERR_TEXTURE_PATH);
	if (map->floor_color.r == -1 || map->floor_color.g == -1
		|| map->floor_color.b == -1)
		return (ERR_COLOR);
	if (map->ceiling_color.r == -1 || map->ceiling_color.g == -1
		|| map->ceiling_color.b == -1)
		return (ERR_COLOR);
	return (SUCCESS);
}
