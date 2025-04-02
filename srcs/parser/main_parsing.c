/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: habouda <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 17:44:05 by emagnani          #+#    #+#             */
/*   Updated: 2025/04/03 00:57:51 by habouda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	get_player_pos(t_cub *cub)
{
	int i;
	int j;
	int found;

	i = 0;
	found = 0;
	while(cub->map->map[i])
	{
		j = 0;
		while(cub->map->map[i][j])
		{
			if (cub->map->map[i][j] && cub->map->map[i][j] >= '2' && cub->map->map[i][j] <= '5')
			{
				found = 1;
				break;
			}
			j++;
		}
		if (found == 1)
			break;
		i++;
	}
	cub->player = malloc(sizeof(t_player) * 1);
	cub->player->pos_x = (double)j + 0.5;
	cub->player->pos_y = (double)i + 0.5;
	printf("Player position set to: x = %f, y = %f\n", cub->player->pos_x, cub->player->pos_y);
	if (cub->map->map[i][j] == '2')
	{
		cub->player->dir_x = 0;
		cub->player->dir_y = -1;
	}
	if (cub->map->map[i][j] == '3')
	{
		cub->player->dir_x = -1;
		cub->player->dir_y = 0;
	}
	if (cub->map->map[i][j] == '4')
	{
		cub->player->dir_x = 1;
		cub->player->dir_y = 0;
	}
	if (cub->map->map[i][j] == '5')
	{
		cub->player->dir_x = 0;
		cub->player->dir_y = 1;
	}
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
