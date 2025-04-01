/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emagnani <emagnani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 15:46:37 by emagnani          #+#    #+#             */
/*   Updated: 2025/03/28 17:30:443 by emagnani         ###   ########.fr       */
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
	{
		close(fd);
		return (err_handler(msg, ERR_MAP_PATH));
	}
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

t_err_status	start_parsing_cub_file(t_map *map, char *file)
{
	int		i;
	int		height;
	int		width;

	if (validate_file_path(file, MSG_INVALID_MAP_PATH) != SUCCESS)
		return (ERR_MAP_PATH);
	init_map(map);
	cub_file_readloop(file, map);
	if (map->map == NULL)
	{
		printf("Map is not correct\n");
		return (ERR_MAP_PATH);
	}
	if (verify_values(map) != SUCCESS)
		return (ERR_VALUES);
	verify_data(map);
	height = get_map_height(map->map);
	width = get_map_width(map->map, height);
	if (width < 3 || height < 3)
	{
		printf("Map is not correct\n");
		return (ERR_VALUES);
	}
	i = is_map_closed(map, height, width);
	if (i == 1)
		printf("Map is not correct\n");
	else 
		printf("Map is correct\n");
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
		printf("no player\n");
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
