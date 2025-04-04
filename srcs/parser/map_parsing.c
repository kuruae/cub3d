/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: habouda <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 14:46:55 by emagnani          #+#    #+#             */
/*   Updated: 2025/04/04 20:11:16 by habouda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	map_reader(char *line, t_map *map, int fd)
{
	int			i;
	int 		fd2;
	char		**full_map;
	char		*translated_line;

	i = 0;
	fd2 = open(TEMP_FILE, O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (fd2 < 0)
	{
		perror("Error opening temporary file");
		return ;
	}
	while (line)
	{
		translated_line = map_translator(line);
		if (!translated_line)
		{
			free(line);
			close(fd2);
			perror("Error translating line");
			return ;
		}
		i++;
		ft_putstr_fd(translated_line, fd2);
		ft_putstr_fd("\n", fd2);
		free(line);
		free(translated_line);
		line = get_next_line(fd);
	}
	full_map = malloc(sizeof(char*) * (i + 1));
	if (!full_map)
	{
		close(fd2);
		perror("Error allocating memory for full_map");
		return ;
	}
	i = 0;
	close(fd2);
	fd2 = open(TEMP_FILE, O_RDONLY);
	if (fd2 < 0)
	{
		free(full_map);
		perror("Error reopening temporary file");
		return ;
	}
	line = get_next_line(fd2);
	while (line)
	{
		trim_newline(line);
		full_map[i] = ft_strdup(line);
		if (!full_map[i])
		{
			free(line);
			while (i-- > 0)
				free(full_map[i]);
			free(full_map);
			close(fd2);
			perror("Error duplicating line");
			return ;
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
	map->map = full_map;
	close(fd2);
	free(line);
}
