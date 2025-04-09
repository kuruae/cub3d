/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xpm.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: habouda <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 00:47:53 by kuru              #+#    #+#             */
/*   Updated: 2025/04/09 18:24:07 by habouda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	write_size_for_current_xpm(t_xpm_size *size, const char *line)
{
	size->width = ft_atoi(line);
	while (ft_isdigit(*line))
		line++;
	while (*line != ' ')
		line++;
	size->height = ft_atoi(line);
	if (size->width < 16 || size->height < 16 || size->width > 800
		|| size->height > 800 || size->width != size->height)
		return (1);
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
	line = get_next_line(fd);
	while (line)
	{
		if (ft_strncmp(&line[0], "\"", 1) == 0 && ft_isdigit(line[1]))
		{
			if (write_size_for_current_xpm(size, &line[1]) != 0)
				err = 1;
			free(line);
			break ;
		}
		free(line);
		line = get_next_line(fd);
	}
	line = get_next_line(fd);
	while (line)
	{
		free(line);
		line = get_next_line(fd);
	}
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

static int	free_xpm_sizes(t_cub *cub)
{
	if (cub->no_size)
		free(cub->no_size);
	if (cub->so_size)
		free(cub->so_size);
	if (cub->we_size)
		free(cub->we_size);
	if (cub->ea_size)
		free(cub->ea_size);
	cub->no_size = NULL;
	cub->so_size = NULL;
	cub->we_size = NULL;
	cub->ea_size = NULL;
	return (1);
}

int	read_all_texture_sizes(t_cub *cub)
{
	if (init_xpm_sizes(cub) != SUCCESS)
		return (free_xpm_sizes(cub));
	if (read_texture_size(cub->map->no_texture, cub->no_size) != 0)
		return (free_xpm_sizes(cub));
	if (read_texture_size(cub->map->so_texture, cub->so_size) != 0)
		return (free_xpm_sizes(cub));
	if (read_texture_size(cub->map->we_texture, cub->we_size) != 0)
		return (free_xpm_sizes(cub));
	if (read_texture_size(cub->map->ea_texture, cub->ea_size) != 0)
		return (free_xpm_sizes(cub));
	return (0);
}
