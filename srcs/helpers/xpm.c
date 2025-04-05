/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xpm.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kuru <kuru@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 00:47:53 by kuru              #+#    #+#             */
/*   Updated: 2025/04/05 17:48:18 by kuru             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


static int	write_size_for_current_xpm(t_xpm_size *size, const char *line)
{
	printf("line: %s\n", line);
	size->width = ft_atoi(line);
	while (ft_isdigit(*line))
		line++;
	while (*line != ' ')
		line++;
	size->height = ft_atoi(line);
	if (size->width < 16 || size->height <= 16 || size->width > 256 || size->height > 256)
	{
		free(size);
		return (1);
	}
	return (0);
}

static int	read_texture_size(const char *texture_path, t_xpm_size *size)
{
	int		fd;
	int		err;
	char	*line;

	err = 0;
	fd = open(texture_path, O_RDONLY);
	if (fd < 0)
		return (1);
	while ((line = get_next_line(fd)))
	{
		if (ft_strncmp(&line[0], "\"", 1) == 0 && ft_isdigit(line[1]))
		{
			if (write_size_for_current_xpm(size, &line[1]) != 0)
				err = 1;
			free(line);
			break;
		}
		free(line);
	}
	while ((line = get_next_line(fd)))
		free(line);
	close(fd);
	return (err);
}

static t_err_status	init_xpm_sizes(t_cub *cub)
{
	cub->no_size = malloc(sizeof(t_xpm_size));
	if (!cub->no_size)
		return (MALLOC_FAILURE);
	cub->so_size = malloc(sizeof(t_xpm_size));
	if (!cub->so_size)
		return (MALLOC_FAILURE);
	cub->we_size = malloc(sizeof(t_xpm_size));
	if (!cub->we_size)
		return (MALLOC_FAILURE);
	cub->ea_size = malloc(sizeof(t_xpm_size));
	if (!cub->ea_size)
		return (MALLOC_FAILURE);
	cub->no_size->width = -1;
	cub->no_size->height = -1;
	cub->so_size->width = -1;
	cub->so_size->height = -1;
	cub->we_size->width = -1;
	cub->we_size->height = -1;
	cub->ea_size->width = -1;
	cub->ea_size->height = -1;
	return (SUCCESS);
}

int	read_all_texture_sizes(t_cub *cub)
{
	if (init_xpm_sizes(cub) != SUCCESS)
		return (1);
	if (read_texture_size(cub->map->no_texture, cub->no_size) != 0)
		return (1);
	if (read_texture_size(cub->map->so_texture, cub->so_size) != 0)
		return (1);
	if (read_texture_size(cub->map->we_texture, cub->we_size) != 0)
		return (1);
	if (read_texture_size(cub->map->ea_texture, cub->ea_size) != 0)
		return (1);
	return (0);
}