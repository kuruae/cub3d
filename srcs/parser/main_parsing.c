/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emagnani <emagnani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 17:44:05 by emagnani          #+#    #+#             */
/*   Updated: 2025/04/13 17:13:10 by emagnani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

t_err_status	validate_file_extension(char *file)
{
	int	len;

	len = ft_strlen(file);
	if (len < 4 || ft_strncmp(&file[len - EXT_LEN], EXT, EXT_LEN))
		return (err_handler(MSG_INVALID_EXT, ERR_MAP_PATH));
	return (SUCCESS);
}

t_err_status	start_parsing(int argc, char **argv, t_map *map)
{
	init_map(map);
	if (argc != 2)
		return (err_handler(MSG_INVALID_ARGS, ERR_MAP_PATH));
	if (validate_file_extension(argv[1]) != SUCCESS)
		return (ERR_MAP_PATH);
	if (start_parsing_cub_file(argv[1], map) != SUCCESS)
	{
		printf("error encoutered in parsing cub file\n");
		return (ERR_MAP_PATH);
	}
	return (SUCCESS);
}
