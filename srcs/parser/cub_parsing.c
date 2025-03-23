/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: habouda <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 15:46:37 by emagnani          #+#    #+#             */
/*   Updated: 2025/03/23 19:04:56 by habouda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <string.h>
#include "cub3d.h"

t_err_status	validate_file_path(const char *file, char *msg)
{
	int	fd;
	// int fd2;

	// fd2 = open("text.txt", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	// if (fd2 < 0) {
	// 	fprintf(stderr, "Error text.txt: %s\n", strerror(errno));
	// 	return ERR_COLOR;
	// }
	// dprintf(fd2, "file: %s\n", file);
	// close(fd2);
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
	map->NO_texture = NULL;
	map->SO_texture = NULL;
	map->WE_texture = NULL;
	map->EA_texture = NULL;
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
	t_map	map;

	if (validate_file_path(file, MSG_INVALID_MAP_PATH) != SUCCESS)
		return (ERR_MAP_PATH);

	debug_print_file(file);

	init_map(&map);

	cub_file_readloop(file, &map);
	
	return (SUCCESS);
}