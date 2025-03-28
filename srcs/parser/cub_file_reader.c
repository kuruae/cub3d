/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_file_reader.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: habouda <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 15:52:41 by emagnani          #+#    #+#             */
/*   Updated: 2025/03/28 20:08:53 by habouda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	trim_newline(char *str)
{
	size_t	len;

	len = ft_strlen(str);
	if (len > 2 && str[len - 1] == '\n')
		str[len - 1] = '\0';
}

bool	are_we_in_map(char *line)
{
	bool	state;

	state = true;
	if (ft_strncmp(line, "NO", 2) == 0)
		state = false;
	if (ft_strncmp(line, "SO", 2) == 0)
		state = false;
	if (ft_strncmp(line, "EA", 2) == 0)
		state = false;
	if (ft_strncmp(line, "WE", 2) == 0)
		state = false;
	if (line[0] == 'F')
		state = false;
	if (line[0] == 'C')
		state = false;
	return (state);
}

int	check_if_empty(char *line)
{
	int	i;

	i = 0;
	if (!line)
		return (0);
	while (line[i] && ft_isspace(line[i]))
	{
		i++;
	}
	if (line[i] == '\0')
		return (0);
	else
		return (1);
}

t_err_status	process_line(char *line, t_map *map, int fd)
{
	t_err_status	status;

	status = SUCCESS;
	trim_newline(line);
	if (check_if_empty(line) == 0)
		return (status);
	if (are_we_in_map(line) == false)
	{
		status = parse_textures(line, map);
		if (status == SUCCESS)
			status = parse_colors(line, map);
	}
	else
	{
		map_reader(line, map, fd);
	}
	return (status);
}

t_err_status	cub_file_readloop(char *file, t_map *map)
{
	int				fd;
	char			*line;
	t_err_status	status;

	status = SUCCESS;
	fd = open(file, O_RDONLY);
	while ((line = get_next_line(fd)))
	{
		status = process_line(line, map, fd);
		free(line);
		if (status != SUCCESS)
			break ;
	}
	close(fd);
	return (SUCCESS);
}
