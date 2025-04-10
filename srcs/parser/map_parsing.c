/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kuru <kuru@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 14:46:55 by emagnani          #+#    #+#             */
/*   Updated: 2025/04/10 20:42:13 by kuru             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	**read_cub(char **full_map, char *line, int fd, int fd2)
{
	int		i;
	char	*translated_line;

	i = 0;
	while (line)
	{
		translated_line = map_translator(line);
		if (!translated_line)
		{
			free(line);
			close(fd2);
			printf("Error translating line\n");
			return (NULL);
		}
		i++;
		ft_putstr_fd(translated_line, fd2);
		ft_putstr_fd("\n", fd2);
		free(translated_line);
		free(line);
		line = get_next_line(fd);
	}
	full_map = malloc(sizeof(char *) * (i + 1));
	if (!full_map)
		return (close(fd2), ft_putstr_fd("Malloc Error", 2), NULL);
	return (full_map);
}

t_err_status	fill_full_map(char **full_map, char *line, int fd2)
{
	int	i;

	i = 0;
	line = get_next_line(fd2);
	while (line)
	{
		trim_newline(line);
		if (line[0] != '\n')
			full_map[i] = ft_strdup(line);
		else
			full_map[i] = ft_strdup("XXXXXXXXXXXX");
		if (!full_map[i])
		{
			free(line);
			while (i-- > 0)
				free(full_map[i]);
			free(full_map);
			return (close(fd2), perror("Malloc Error"), MALLOC_FAILURE);
		}
		free(line);
		line = get_next_line(fd2);
		i++;
	}
	full_map[i] = NULL;
	return (SUCCESS);
}

t_err_status	map_reader(char *line, t_map *map, int fd)
{
	int		fd2;
	char	**full_map;

	full_map = NULL;
	fd2 = open(TEMP_FILE, O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (fd2 < 0)
		return (ft_putstr_fd("Error opening temp file", 2), MALLOC_FAILURE);
	full_map = read_cub(full_map, line, fd, fd2);
	if (!full_map)
		return (MALLOC_FAILURE);
	close(fd2);
	fd2 = open(TEMP_FILE, O_RDONLY);
	if (fd2 < 0)
	{
		perror("Error reopening temporary file");
		ft_free_str_array(&full_map);
		return (MALLOC_FAILURE);
	}
	if (fill_full_map(full_map, line, fd2) != SUCCESS)
		return (MALLOC_FAILURE);
	if (check_for_x(full_map))
		return (ft_free_str_array(&full_map), ERR_INVALID_MAP);
	map->map = full_map;
	return (close(fd2), SUCCESS);
}
