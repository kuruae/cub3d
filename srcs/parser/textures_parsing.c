/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures_parsing.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emagnani <emagnani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 18:23:19 by emagnani          #+#    #+#             */
/*   Updated: 2025/04/07 18:06:09 by emagnani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static t_err_status	process_texture(const char *line, char **texture)
{
	while (ft_isspace(*line))
		line++;
	if (ft_strncmp(line, "./", 2) != 0)
		return (ERR_TEXTURE_PATH);
	line += 2;
	printf("line: %s\n", line);
	if (validate_file_path(line, MSG_INVALID_TEXTURE_PATH) != SUCCESS)
		return (ERR_TEXTURE_PATH);
	if (*texture)
		free(*texture);
	*texture = ft_strdup(line);
	if (!*texture)
		return (MALLOC_FAILURE);
	return (SUCCESS);
}

t_err_status	parse_textures(char *line, t_map *map)
{
	t_err_status status;

	status = SUCCESS;
	if (ft_strncmp(line, "NO", 2) == 0 && status == SUCCESS)
		status = process_texture(&line[2], &map->no_texture);
	else if (ft_strncmp(line, "SO", 2) == 0 && status == SUCCESS)
		status = process_texture(&line[2], &map->so_texture);
	else if (ft_strncmp(line, "WE", 2) == 0 && status == SUCCESS)
		status = process_texture(&line[2], &map->we_texture);
	else if (ft_strncmp(line, "EA", 2) == 0 && status == SUCCESS)
		status = process_texture(&line[2], &map->ea_texture);
	return (status);
}