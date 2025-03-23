/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_colors.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: habouda <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 15:52:41 by emagnani          #+#    #+#             */
/*   Updated: 2025/03/23 17:20:28 by habouda          ###   ########.fr       */
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
	t_err_status	status;

	status = SUCCESS;
	if (ft_strncmp(line, "NO", 2) == 0 && status == SUCCESS)
		status = process_texture(&line[2], &map->NO_texture);
	else if (ft_strncmp(line, "SO", 2) == 0 && status == SUCCESS)
		status = process_texture(&line[2], &map->SO_texture);
	else if (ft_strncmp(line, "WE", 2) == 0 && status == SUCCESS)
		status = process_texture(&line[2], &map->WE_texture);
	else if (ft_strncmp(line, "EA", 2) == 0 && status == SUCCESS)
		status = process_texture(&line[2], &map->EA_texture);
	return (status);
}

static void trim_newline(char *str)
{
    size_t len = ft_strlen(str);
    if (len > 2 && str[len - 1] == '\n')
        str[len - 1] = '\0';
}

t_err_status	texture_and_colors_parsing(char *file, t_map *map)
{
	int				fd;
	char			*line;
	t_err_status	status;
	
	status = SUCCESS;
	fd = open(file, O_RDONLY);
	
	while ((line = get_next_line(fd)))
	{
		trim_newline(line);
		status = parse_textures(line, map);

		// if (line[0] == 'F')
		// 	process_color(line, &map->floor_color);
		// else if (line[0] == 'C')
		// 	process_color(line, &map->ceiling_color);
		
		free(line);

		if (status != SUCCESS)
			return (status);
	}
	
	
	return (SUCCESS);
}