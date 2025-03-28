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

#include <errno.h>
#include <string.h>
#include "cub3d.h"

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
	int i;
	t_map	map;

	if (validate_file_path(file, MSG_INVALID_MAP_PATH) != SUCCESS)
		return (ERR_MAP_PATH);

	// debug_print_file(file);

	init_map(&map);

	cub_file_readloop(file, &map);
	// parse_map(&map);
	verify_values(&map);
	// verify_blabla(&map);
	i = is_map_closed(&map, get_map_height(map.map), get_map_width(map.map, get_map_height(map.map)));
	fprintf(stderr, "CODE DERREUR DE MAP CHECKER EST :%d\n", i);
	get_map_height(map.map);
	get_map_width(map.map, get_map_height(map.map));
	debug_print_struct_map(&map);
	
	return (SUCCESS);
}

t_err_status	verify_values(t_map *map)
{
	int	i;
	int j;
	int	pos;

	pos = 0;
	i = 0;
	while(map->map[i])
	{
		j = 0;
		while(map->map[i][j] != -1)
		{
			if (map->map[i][j] >= 2 && map->map[i][j] <= 6)
				pos++;
			j++;
		}
		i++;
	}
	if (pos != 1)
		return (ERR_POSITION);
	return (SUCCESS);
}

t_err_status	verify_blabla(t_map *map)
{
	if (!map->no_texture || !map->so_texture || !map->we_texture || !map->ea_texture)
		return (ERR_TEXTURE_PATH);
	if (map->floor_color.r == -1 || map->floor_color.g == -1 || map->floor_color.b == -1)
		return (ERR_COLOR);
	if (map->ceiling_color.r == -1 || map->ceiling_color.g == -1 || map->ceiling_color.b == -1)
		return (ERR_COLOR);
	return (SUCCESS);
}


int		is_map_closed(t_map *map, int height, int width)
{
	int	i;
	int	*up;

	i = 0;
	up = malloc(sizeof(int*) * width);
	while (i != width)
	{
		while (map->map[i] != 6 && map->map[i] != -1)

		i++;
	}
}


// int	is_map_closed(t_map *map, int height, int width)
// {
// 	int	i;
// 	int	len;
// 	int j;

// 	i = 0;
// 	while (map->map[i] != -1)
// 	{
// 		j = 0;
// 		while (map->map[i][j] == "6")
// 			j++;
// 		if (map->map[i][j] == "0")
// 			return (EXIT_FAILURE);
// 		if (i != width && i != 0)
// 		{
// 			len = get_biggest_tablen(map->map[i], map->map[i - 1], map->map[i + 1]);
// 		}
// 	}
// }



// int		check_extremes

// int		get_biggest_tablen(int *tab1, int *tab2, int *tab3)
// {
// 	int	i;
// 	int j;
// 	int k;

// 	i = tablen(tab1);
// 	j = tablen(tab2);
// 	k =	tablen(tab3);
// 	if (i >= k && i >= j)
// 		return (i);
// 	if (j >= k && j >= i)
// 		return (j);
// 	if (k >= i && k >= j)
// 		return (k);
// }

// int		tablen(int *tab)
// {
// 	int	i;

// 	i = 0;
// 	while(tab[i] != -1)
// 		i++;
// 	return (i);
// }