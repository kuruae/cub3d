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

t_err_status	start_parsing_cub_file(char *file)
{
	int		i;
	int		height;
	int		width;
	t_map	map;

	if (validate_file_path(file, MSG_INVALID_MAP_PATH) != SUCCESS)
		return (ERR_MAP_PATH);
	// debug_print_file(file);
	init_map(&map);
	cub_file_readloop(file, &map);
	verify_values(&map);
	verify_data(&map);
	height = get_map_height(map.map);
	width = get_map_width(map.map, height);
	printf("height : %d , widht %d\n", height, width);
	i = is_map_closed(&map, height, width);
	if (i == 0)
		printf("ouistiti\n");
	// fprintf(stderr, "CODE DERREUR DE MAP CHECKER EST :%d\n", i);
	// debug_print_struct_map(&map);
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
			if (map->map[i][j] >= NORTH && map->map[i][j] <= VOID)
				pos++;
			j++;
		}
		i++;
	}
	if (pos != 1)
		return (ERR_POSITION);
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
