/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emagnani <emagnani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 17:53:27 by emagnani          #+#    #+#             */
/*   Updated: 2025/03/28 18:06:07 by emagnani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void debug_print_file(char *file)
{
	int		fd;
	char	*line;

	fd = open(file, O_RDONLY);
	while ((line = get_next_line(fd)))
	{
		printf("%s\n", line);
		free(line);
	}
	free(line);
	close(fd);
}

void	debug_print_struct_map(t_map *map)
{
	printf("no_texture: %s\n", map->no_texture);
	printf("so_texture: %s\n", map->so_texture);
	printf("we_texture: %s\n", map->we_texture);
	printf("ea_texture: %s\n", map->ea_texture);
	printf("floor_color: %d, %d, %d\n", map->floor_color.r, map->floor_color.g, map->floor_color.b);
	printf("ceiling_color: %d, %d, %d\n", map->ceiling_color.r, map->ceiling_color.g, map->ceiling_color.b);
}


void	debug_print_translated_line(int *translated_line)
{
	int	i;

	i = 0;
	while(translated_line[i] != -1)
	{
		fprintf(stderr, " %d", translated_line[i]);
		i++;
	}
	fprintf(stderr, "\n");
}

void	debug_print_full_map(int **full_map)
{
	int	i;
	int	j;

	i = 0;
	while(full_map[i])
	{
		j = 0;
		while(full_map[i][j] != -1)
		{
			fprintf(stderr, " %d", full_map[i][j]);
			j++;
		}
		fprintf(stderr, "\n");
		i++;
	}
}
