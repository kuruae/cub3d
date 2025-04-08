/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: habouda <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 14:46:55 by emagnani          #+#    #+#             */
/*   Updated: 2025/04/08 19:13:24 by habouda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_err_status	map_reader(char *line, t_map *map, int fd)
{
	int		i;
	int		fd2;
	char	**full_map;
	char	*translated_line;

	i = 0;
	fd2 = open(TEMP_FILE, O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (fd2 < 0)
	{
		perror("Error opening temporary file");
		return (MALLOC_FAILURE);
	}
	while (line)
	{
		translated_line = map_translator(line);
		if (!translated_line)
		{
			free(line);
			close(fd2);
			printf("Error translating line\n");
			return (MALLOC_FAILURE);
		}
		i++;
		ft_putstr_fd(translated_line, fd2);
		ft_putstr_fd("\n", fd2);
		free(line);
		free(translated_line);
		line = get_next_line(fd);
	}
	full_map = malloc(sizeof(char *) * (i + 1));
	if (!full_map)
	{
		close(fd2);
		perror("Error allocating memory for full_map");
		return (MALLOC_FAILURE);
	}
	i = 0;
	close(fd2);
	fd2 = open(TEMP_FILE, O_RDONLY);
	if (fd2 < 0)
	{
		free(full_map);
		perror("Error reopening temporary file");
		return (MALLOC_FAILURE);
	}
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
			close(fd2);
			perror("Error duplicating line");
			return (MALLOC_FAILURE);
		}
		free(line);
		line = get_next_line(fd2);
		i++;
	}
	full_map[i] = NULL;
	i = 0;
	while (full_map[i] != NULL)
	{
		printf("%s\n", full_map[i]);
		i++;
	}
	if (check_for_X(full_map))
	{
		ft_free_str_array(&full_map);
		return (ERR_INVALID_MAP);
	}	
	map->map = full_map;
	close(fd2);
	free(line);
	return (SUCCESS);
}
